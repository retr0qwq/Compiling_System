#include "backend/targets/riscv64/rv64_defs.h"
#include <backend/targets/riscv64/passes/lowering/frame_lowering.h>
#include <debug.h>

namespace BE::RV64::Passes::Lowering
{
    void FrameLoweringPass::runOnModule(BE::Module& module)
    {
        for (auto* func : module.functions) runOnFunction(func);
    }

    void FrameLoweringPass::runOnFunction(BE::Function* func) 
    {  
        // 计算栈帧对象偏移
        func->frameInfo.calculateOffsets();

        // 设置函数的总栈大小（使用 MFrameInfo 的公有接口）
        func->stackSize = func->frameInfo.getStackSize();

        // 1) 将物理寄存器参数搬入虚拟寄存器（在入口基本块前端插入 move）
        if (!func->params.empty())
        {
            // 选择 entry block（map 有序，首项为入口）
            BE::Block* entry = nullptr;
            if (!func->blocks.empty()) entry = func->blocks.begin()->second;
            if (entry)
            {
                // 为保持参数顺序，逆序在前端插入
                for (int i = static_cast<int>(func->params.size()) - 1; i >= 0; --i)
                {
                    BE::Register phys = func->params[i];
                    if (!phys.isVreg)
                    {
                        BE::Register vreg = BE::getVReg(phys.dt);
                        // move vreg <- phys
                        entry->insts.push_front(BE::createMove(new BE::RegOperand(vreg), new BE::RegOperand(phys)));
                        func->params[i] = vreg;
                    }
                }
            }
        }

        // 如果函数有 incoming stack params，则在 prologue 中设置 fp = sp
        if (func->hasStackParam)
        {
            BE::Block* entry = nullptr;
            if (!func->blocks.empty()) entry = func->blocks.begin()->second;
            if (entry)
            {
                // 使用 ADDI fp, sp, 0
                entry->insts.push_front(BE::RV64::createIInst(BE::RV64::Operator::ADDI, BE::RV64::PR::fp, BE::RV64::PR::sp, 0));
            }
        }

        // 2) 解析所有含 FrameIndexOperand 的目标指令
        // 使用索引遍历，因为插入指令会改变迭代器
        for (auto& [bid, block] : func->blocks)
        {
            auto& insts = block->insts;
            
            // 使用索引而不是迭代器，因为要插入指令
            for (size_t idx = 0; idx < insts.size(); ++idx)
            {
                auto* ti = dynamic_cast<BE::RV64::Instr*>(insts[idx]);
                if (!ti) continue;

                if (ti->use_ops && ti->fiop && ti->fiop->ot == BE::Operand::Type::FRAME_INDEX)
                {
                    BE::FrameIndexOperand* fiOp = static_cast<BE::FrameIndexOperand*>(ti->fiop);

                    // 仅解析 Local/Outgoing object（pre-RA 不处理 SpillSlot）
                    int offset = func->frameInfo.getObjectOffset(fiOp->frameIndex);
                    if (offset < 0)
                    {
                        // 该 FrameIndex 可能属于 spill slot，留待 Post-RA 处理，跳过
                        continue;
                    }

                    // 判定基址寄存器与是否为 store 指令
                    BE::Register baseReg = func->hasStackParam ? BE::RV64::PR::fp : BE::RV64::PR::sp;
                    bool isStore = (ti->op == BE::RV64::Operator::SW || ti->op == BE::RV64::Operator::SD ||
                                    ti->op == BE::RV64::Operator::FSW || ti->op == BE::RV64::Operator::FSD);

                    // 若偏移可由 12 位立即数表示，直接改为 base + imm 的形式
                    if (offset >= -2048 && offset <= 2047)
                    {
                        ti->use_ops = false;
                        if (isStore)
                        {
                            ti->rs2  = baseReg; // store 的基址在 rs2
                            ti->imme = offset;
                        }
                        else
                        {
                            ti->rs1  = baseReg; // load/其他的基址在 rs1
                            ti->imme = offset;
                        }
                        ti->fiop = nullptr;
                    }
                    else
                    {
                        // 需要展开为 LUI + ADD (+ ADDI) 序列：生成 addr 在临时 vreg 中
                        BE::Register addr = BE::getVReg(BE::I64);

                        // 计算 hi/lo：使 lo 在 signed 12-bit 范围内
                        int hi = (offset + 0x800) & ~0xfff;
                        int lo = offset - hi;
                        
                        // 先插入LUI指令
                        auto luiInst = BE::RV64::createUInst(BE::RV64::Operator::LUI, addr, hi);
                        insts.insert(insts.begin() + idx, luiInst);
                        idx++; // 索引递增，因为插入了新指令
                        
                        // 插入ADD指令：将高位与基址寄存器相加
                        auto addInst = BE::RV64::createRInst(BE::RV64::Operator::ADD, addr, addr, baseReg);
                        insts.insert(insts.begin() + idx, addInst);
                        idx++;
                        
                        // 如果lo不为0，插入ADDI指令
                        if (lo != 0)
                        {
                            auto addiInst = BE::RV64::createIInst(BE::RV64::Operator::ADDI, addr, addr, lo);
                            insts.insert(insts.begin() + idx, addiInst);
                            idx++;
                        }
                        
                        // 修改原指令：使用计算出的地址寄存器作为基址
                        // 原指令现在在idx位置（因为我们已经插入了多条指令）
                        ti = dynamic_cast<BE::RV64::Instr*>(insts[idx]); // 重新获取指针
                        if (ti)
                        {
                            if (isStore)
                                ti->rs2 = addr;
                            else
                                ti->rs1 = addr;
                            ti->use_ops = false;
                            ti->imme = 0;
                            ti->fiop = nullptr;
                        }
                        
                        // idx现在指向原指令，下一次循环会++idx，跳过这条已经处理的指令
                    }
                }
            }
        }
    }

}  // namespace BE::RV64::Passes::Lowering
