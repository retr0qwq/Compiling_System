#include <backend/targets/riscv64/passes/lowering/stack_lowering.h>
#include <backend/mir/m_function.h>
#include <backend/mir/m_instruction.h>
#include <backend/mir/m_defs.h>
#include <backend/targets/riscv64/rv64_defs.h>
#include <algorithm>
#include <backend/targets/riscv64/rv64_reg_info.h>

namespace BE::RV64::Passes::Lowering
{
    void StackLoweringPass::runOnModule(BE::Module& module)
    {
        for (auto* func : module.functions) lowerFunction(func);
    }

    void StackLoweringPass::lowerFunction(BE::Function* func) 
    {   
        // 重新计算帧（包含 RA 创建的 SpillSlot）并更新函数栈大小
        func->frameInfo.calculateOffsets();
        func->stackSize = func->frameInfo.getStackSize();

        // 收集函数中使用到的物理寄存器（Post-RA，应为物理寄存器）
        std::set<uint32_t> usedIntRegs;
        std::set<uint32_t> usedFloatRegs;

        for (auto& [bid, block] : func->blocks)
        {
            for (auto inst : block->insts)
            {
                if (auto* ti = dynamic_cast<BE::RV64::Instr*>(inst))
                {
                    if (!ti->rd.isVreg && ti->rd.rId >= 0) 
                        usedIntRegs.insert(ti->rd.rId);
                    if (!ti->rs1.isVreg && ti->rs1.rId >= 0) 
                        usedIntRegs.insert(ti->rs1.rId);
                    if (!ti->rs2.isVreg && ti->rs2.rId >= 0) 
                        usedIntRegs.insert(ti->rs2.rId);
                    
                    // 检查浮点寄存器
                    if (ti->rd.dt == BE::F32 || ti->rd.dt == BE::F64)
                        usedFloatRegs.insert(ti->rd.rId);
                    if (ti->rs1.dt == BE::F32 || ti->rs1.dt == BE::F64)
                        usedFloatRegs.insert(ti->rs1.rId);
                    if (ti->rs2.dt == BE::F32 || ti->rs2.dt == BE::F64)
                        usedFloatRegs.insert(ti->rs2.rId);
                }
                else if (auto* fil = dynamic_cast<BE::FILoadInst*>(inst))
                {
                    if (!fil->dest.isVreg) usedIntRegs.insert(fil->dest.rId);
                }
                else if (auto* fis = dynamic_cast<BE::FIStoreInst*>(inst))
                {
                    if (!fis->src.isVreg) usedIntRegs.insert(fis->src.rId);
                }
                else if (auto* mv = dynamic_cast<BE::MoveInst*>(inst))
                {
                    if (mv->src && mv->src->ot == BE::Operand::Type::REG)
                    {
                        auto* ro = static_cast<BE::RegOperand*>(mv->src);
                        if (!ro->reg.isVreg && ro->reg.rId >= 0) 
                            usedIntRegs.insert(ro->reg.rId);
                    }
                    if (mv->dest && mv->dest->ot == BE::Operand::Type::REG)
                    {
                        auto* ro = static_cast<BE::RegOperand*>(mv->dest);
                        if (!ro->reg.isVreg && ro->reg.rId >= 0) 
                            usedIntRegs.insert(ro->reg.rId);
                    }
                }
            }
        }

        // RISC-V 64位的被调者保存寄存器
        // 整数: s0-s11 (x8-x9, x18-x27)
        // 浮点: fs0-fs11 (f8-f9, f18-f27)
        const std::vector<int> calleeSavedInt = {8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
        // 浮点寄存器编号在 PR enum 中位于 32..63，因此需要加上32的偏移
        const std::vector<int> calleeSavedFloat = {32 + 8, 32 + 9, 32 + 18, 32 + 19, 32 + 20, 32 + 21,
                               32 + 22, 32 + 23, 32 + 24, 32 + 25, 32 + 26, 32 + 27};

        // 计算需要保存的寄存器列表（只保存真正被使用且为 callee-saved 的寄存器）
        std::vector<uint32_t> toSaveInt;
        std::vector<uint32_t> toSaveFloat;
        for (int r : calleeSavedInt)
            if (usedIntRegs.count(static_cast<uint32_t>(r))) 
                toSaveInt.push_back(static_cast<uint32_t>(r));
        for (int r : calleeSavedFloat)
            if (usedFloatRegs.count(static_cast<uint32_t>(r))) // 修正：使用usedFloatRegs
                toSaveFloat.push_back(static_cast<uint32_t>(r));

        // 计算保存区总大小（按8字节对齐保存）并加入到函数最终栈大小
        int saveAreaSize = static_cast<int>(toSaveInt.size() + toSaveFloat.size()) * 8;
        // 对齐到16字节
        auto alignTo = [](int v, int a) { return (v + (a - 1)) & ~(a - 1); };
        saveAreaSize = alignTo(saveAreaSize, 16);

        // 将保存区计入最终函数栈大小（Post-RA 阶段确定）
        func->stackSize = alignTo(func->stackSize + saveAreaSize, func->frameInfo.getBaseAlignment());

        // 选择入口块并确定插入位置：在现有前导 prologue 之后插入
        BE::Block* entry = nullptr;
        if (!func->blocks.empty()) entry = func->blocks.begin()->second;

        if (entry)
        {
            // 找到插入点：跳过前面的MoveInst与fp=sp（ADDI fp, sp, 0）指令
            size_t insertPos = 0;
            while (insertPos < entry->insts.size())
            {
                auto* i = entry->insts[insertPos];
                if (dynamic_cast<BE::MoveInst*>(i)) { insertPos++; continue; }
                if (auto* ti = dynamic_cast<BE::RV64::Instr*>(i))
                {
                    if (ti->op == BE::RV64::Operator::ADDI && ti->rd == BE::RV64::PR::fp && ti->rs1 == BE::RV64::PR::sp)
                    {
                        insertPos++;
                        continue;
                    }
                }
                break;
            }

            // 首先调整栈指针：sp = sp - stackSize
            int adjust = -func->stackSize;
            if (adjust >= -2048 && adjust <= 2047)
            {
                auto adj = BE::RV64::createIInst(BE::RV64::Operator::ADDI, BE::RV64::PR::sp, BE::RV64::PR::sp, adjust);
                entry->insts.insert(entry->insts.begin() + insertPos, adj);
                insertPos++;
            }
            else
            {
                // 需要使用临时寄存器 t0 计算大立即数
                BE::Register t0 = BE::RV64::PR::t0;
                int hi = (adjust + 0x800) & ~0xfff;  // 高20位
                int lo = adjust - hi;                // 低12位
                
                auto lui = BE::RV64::createUInst(BE::RV64::Operator::LUI, t0, hi);
                entry->insts.insert(entry->insts.begin() + insertPos, lui);
                insertPos++;
                
                auto add = BE::RV64::createRInst(BE::RV64::Operator::ADD, t0, t0, BE::RV64::PR::sp);
                entry->insts.insert(entry->insts.begin() + insertPos, add);
                insertPos++;
                
                if (lo != 0)
                {
                    auto addi = BE::RV64::createIInst(BE::RV64::Operator::ADDI, BE::RV64::PR::sp, t0, lo);
                    entry->insts.insert(entry->insts.begin() + insertPos, addi);
                    insertPos++;
                }
                else
                {
                    auto mv = BE::RV64::createRInst(BE::RV64::Operator::ADD, BE::RV64::PR::sp, t0, BE::RV64::PR::x0);
                    entry->insts.insert(entry->insts.begin() + insertPos, mv);
                    insertPos++;
                }
            }

            // 保存被调者保存寄存器（使用正偏移，因为sp已经调整）
            int saveOffset = 0;
            for (uint32_t rid : toSaveInt)
            {
                BE::Register preg = BE::RV64::PR::getPR(rid);
                // 使用正偏移：SD preg, offset(sp)
                auto store = BE::RV64::createSInst(BE::RV64::Operator::SD, preg, BE::RV64::PR::sp, saveOffset);
                entry->insts.insert(entry->insts.begin() + insertPos, store);
                insertPos++;
                saveOffset += 8;
            }
            for (uint32_t rid : toSaveFloat)
            {
                BE::Register preg = BE::RV64::PR::getPR(rid);
                // 浮点存储：FSD preg, offset(sp)
                auto store = BE::RV64::createSInst(BE::RV64::Operator::FSD, preg, BE::RV64::PR::sp, saveOffset);
                entry->insts.insert(entry->insts.begin() + insertPos, store);
                insertPos++;
                saveOffset += 8;
            }
        }

        // 替换 FILoadInst / FIStoreInst 为具体访存指令（使用 sp 作为基址，偏移为 spill slot offset）
        for (auto& [bid, block] : func->blocks)
        {
            auto& insts = block->insts;
            for (size_t i = 0; i < insts.size(); ++i)
            {
                if (auto* fil = dynamic_cast<BE::FILoadInst*>(insts[i]))
                {
                    int off = func->frameInfo.getSpillSlotOffset(fil->frameIndex);
                    if (off < 0) { 
                        ERROR("Bad spill slot offset for frame index: %d", fil->frameIndex); 
                        continue; 
                    }

                    BE::Register rd = fil->dest;
                    // 选择加载指令类型
                    BE::RV64::Operator op = BE::RV64::Operator::LD;
                    if (rd.dt == BE::I32) op = BE::RV64::Operator::LW;
                    else if (rd.dt == BE::F32) op = BE::RV64::Operator::FLW;
                    else if (rd.dt == BE::F64) op = BE::RV64::Operator::FLD;

                    BE::MInstruction::delInst(insts[i]);
                    insts[i] = BE::RV64::createIInst(op, rd, BE::RV64::PR::sp, off);
                }
                else if (auto* fis = dynamic_cast<BE::FIStoreInst*>(insts[i]))
                {
                    int off = func->frameInfo.getSpillSlotOffset(fis->frameIndex);
                    if (off < 0) { 
                        ERROR("Bad spill slot offset for frame index: %d", fis->frameIndex); 
                        continue; 
                    }

                    BE::Register rs = fis->src;
                    BE::RV64::Operator op = BE::RV64::Operator::SD;
                    if (rs.dt == BE::I32) op = BE::RV64::Operator::SW;
                    else if (rs.dt == BE::F32) op = BE::RV64::Operator::FSW;
                    else if (rs.dt == BE::F64) op = BE::RV64::Operator::FSD;

                    BE::MInstruction::delInst(insts[i]);
                    insts[i] = BE::RV64::createSInst(op, rs, BE::RV64::PR::sp, off);
                }
            }
        }

        // 在每个返回点插入恢复序列：先恢复保存的寄存器，再恢复sp
        for (auto& [bid, block] : func->blocks)
        {
            auto& insts = block->insts;
            for (size_t i = 0; i < insts.size(); ++i)
            {
                if (auto* ti = dynamic_cast<BE::RV64::Instr*>(insts[i]))
                {
                    if (ti->op == BE::RV64::Operator::RET)
                    {
                        size_t insertAt = i; // 在 return 之前插入

                        // 先恢复保存的寄存器（逆序）
                        int restoreOffset = (toSaveInt.size() + toSaveFloat.size() - 1) * 8;
                        
                        // 恢复浮点寄存器
                        for (int k = static_cast<int>(toSaveFloat.size()) - 1; k >= 0; --k)
                        {
                            uint32_t rid = toSaveFloat[k];
                            BE::Register preg = BE::RV64::PR::getPR(rid);
                            auto ld = BE::RV64::createIInst(BE::RV64::Operator::FLD, preg, BE::RV64::PR::sp, restoreOffset);
                            insts.insert(insts.begin() + insertAt, ld);
                            insertAt++;
                            restoreOffset -= 8;
                        }
                        
                        // 恢复整数寄存器
                        for (int k = static_cast<int>(toSaveInt.size()) - 1; k >= 0; --k)
                        {
                            uint32_t rid = toSaveInt[k];
                            BE::Register preg = BE::RV64::PR::getPR(rid);
                            auto ld = BE::RV64::createIInst(BE::RV64::Operator::LD, preg, BE::RV64::PR::sp, restoreOffset);
                            insts.insert(insts.begin() + insertAt, ld);
                            insertAt++;
                            restoreOffset -= 8;
                        }

                        // 恢复栈指针：sp = sp + stackSize
                        int adj = func->stackSize;
                        if (adj >= -2048 && adj <= 2047)
                        {
                            auto adjInst = BE::RV64::createIInst(BE::RV64::Operator::ADDI, BE::RV64::PR::sp, BE::RV64::PR::sp, adj);
                            insts.insert(insts.begin() + insertAt, adjInst);
                            insertAt++;
                        }
                        else
                        {
                            BE::Register t0 = BE::RV64::PR::t0;
                            int hi = (adj + 0x800) & ~0xfff;
                            int lo = adj - hi;
                            
                            auto lui = BE::RV64::createUInst(BE::RV64::Operator::LUI, t0, hi);
                            insts.insert(insts.begin() + insertAt, lui);
                            insertAt++;
                            
                            auto add = BE::RV64::createRInst(BE::RV64::Operator::ADD, t0, t0, BE::RV64::PR::sp);
                            insts.insert(insts.begin() + insertAt, add);
                            insertAt++;
                            
                            if (lo != 0)
                            {
                                auto addi = BE::RV64::createIInst(BE::RV64::Operator::ADDI, BE::RV64::PR::sp, t0, lo);
                                insts.insert(insts.begin() + insertAt, addi);
                                insertAt++;
                            }
                            else
                            {
                                auto mv = BE::RV64::createRInst(BE::RV64::Operator::ADD, BE::RV64::PR::sp, t0, BE::RV64::PR::x0);
                                insts.insert(insts.begin() + insertAt, mv);
                                insertAt++;
                            }
                        }

                        // 跳过刚插入的指令
                        i = insertAt;
                    }
                }
            }
        }
    }
}  // namespace BE::RV64::Passes::Lowering
