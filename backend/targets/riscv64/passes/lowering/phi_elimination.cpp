#include <backend/targets/riscv64/passes/lowering/phi_elimination.h>
#include <debug.h>
#include <algorithm>

namespace BE::RV64::Passes::Lowering
{
    using namespace BE;
    using namespace BE::RV64;

    void PhiEliminationPass::runOnModule(BE::Module& module, const BE::Targeting::TargetInstrAdapter* adapter)
    {
        if (module.functions.empty()) return;
        for (auto* func : module.functions) runOnFunction(func, adapter);
    }

    void PhiEliminationPass::runOnFunction(BE::Function* func, const BE::Targeting::TargetInstrAdapter* adapter)
    {
        if (!func) return;

        // 对每个基本块，查找 PHI 指令并在对应前驱块插入 move
        for (auto& [bid, block] : func->blocks)
        {
            auto& insts = block->insts;

            // 收集所有 phi 指令的位置（index）
            std::vector<size_t> phiIdxs;
            for (size_t i = 0; i < insts.size(); ++i)
            {
                if (dynamic_cast<PhiInst*>(insts[i])) phiIdxs.push_back(i);
            }

            // 逆序处理，便于删除
            for (auto it = phiIdxs.rbegin(); it != phiIdxs.rend(); ++it)
            {
                size_t idx = *it;
                auto* phi = static_cast<PhiInst*>(insts[idx]);
                if (!phi) continue;

                Register dst = phi->resReg;

                // 对于每个 incoming 值，在对应前驱块插入 move
                for (auto& [labelId, srcOp] : phi->incomingVals)
                {
                    // labelId 对应前驱基本块 id
                    auto fit = func->blocks.find(labelId);
                    if (fit == func->blocks.end())
                    {
                        ERROR("PhiElim: predecessor block %u not found", labelId);
                        continue;
                    }

                    BE::Block* pred = fit->second;

                    // 选择插入点：放在前驱块的 terminator 之前
                    size_t insertPos = pred->insts.size();
                    if (insertPos > 0)
                    {
                        // 若末尾为分支/返回等 terminator，则向前移动一个位置
                        auto* last = dynamic_cast<BE::RV64::Instr*>(pred->insts.back());
                        if (last)
                        {
                            switch (last->op)
                            {
                                case BE::RV64::Operator::BEQ:
                                case BE::RV64::Operator::BNE:
                                case BE::RV64::Operator::BLT:
                                case BE::RV64::Operator::BGE:
                                case BE::RV64::Operator::BLTU:
                                case BE::RV64::Operator::BGEU:
                                case BE::RV64::Operator::BGT:
                                case BE::RV64::Operator::BLE:
                                case BE::RV64::Operator::BGTU:
                                case BE::RV64::Operator::BLEU:
                                case BE::RV64::Operator::JAL:
                                case BE::RV64::Operator::JALR:
                                case BE::RV64::Operator::RET:
                                    insertPos--;
                                    break;
                                default: break;
                            }
                        }
                    }

                    // 根据 srcOp 类型构造合适的操作数
                    BE::Operand* movSrc = nullptr;
                    switch (srcOp->ot)
                    {
                        case BE::Operand::Type::REG:
                        {
                            auto* ro = static_cast<RegOperand*>(srcOp);
                            movSrc = new RegOperand(ro->reg);
                            break;
                        }
                        case BE::Operand::Type::IMMI32:
                        {
                            auto* io = static_cast<I32Operand*>(srcOp);
                            movSrc = new I32Operand(io->val);
                            break;
                        }
                        case BE::Operand::Type::IMMF32:
                        {
                            auto* fo = static_cast<F32Operand*>(srcOp);
                            movSrc = new F32Operand(fo->val);
                            break;
                        }
                        default:
                            ERROR("Unsupported PHI incoming operand type");
                            continue;
                    }

                    // 目标操作数
                    BE::Operand* movDst = new RegOperand(dst);

                    // 插入 move 指令（使用实际的RISC-V指令，而不是伪指令）
                    // Move伪指令消解：将Move指令转换为实际的RISC-V指令
                    if (movSrc->ot == BE::Operand::Type::REG)
                    {
                        // 寄存器到寄存器的移动：使用 addi rd, rs, 0
                        auto* srcReg = static_cast<RegOperand*>(movSrc);
                        auto* dstReg = static_cast<RegOperand*>(movDst);
                        
                        auto* moveInst = BE::RV64::createIInst(
                            BE::RV64::Operator::ADDI,
                            dstReg->reg,
                            srcReg->reg,
                            0
                        );
                        pred->insts.insert(pred->insts.begin() + insertPos, moveInst);
                    }
                    else if (movSrc->ot == BE::Operand::Type::IMMI32)
                    {
                        // 立即数移动：使用 addi rd, x0, imm 或 li伪指令
                        auto* immOp = static_cast<I32Operand*>(movSrc);
                        auto* dstReg = static_cast<RegOperand*>(movDst);
                        
                        int32_t imm = immOp->val;
                        
                        if (imm >= -2048 && imm <= 2047)
                        {
                            // 小立即数：使用 addi
                            auto* moveInst = BE::RV64::createIInst(
                                BE::RV64::Operator::ADDI,
                                dstReg->reg,
                                BE::RV64::PR::x0,  // 零寄存器
                                imm
                            );
                            pred->insts.insert(pred->insts.begin() + insertPos, moveInst);
                        }
                        else
                        {
                            // 大立即数：需要分解为 lui + addi
                            // 先插入 lui 指令加载高位
                            int32_t hi = (imm + 0x800) & ~0xFFF;
                            int32_t lo = imm - hi;
                            
                            auto* luiInst = BE::RV64::createUInst(
                                BE::RV64::Operator::LUI,
                                dstReg->reg,
                                hi
                            );
                            pred->insts.insert(pred->insts.begin() + insertPos, luiInst);
                            insertPos++;
                            
                            // 再插入 addi 指令加上低位
                            if (lo != 0)
                            {
                                auto* addiInst = BE::RV64::createIInst(
                                    BE::RV64::Operator::ADDI,
                                    dstReg->reg,
                                    dstReg->reg,
                                    lo
                                );
                                pred->insts.insert(pred->insts.begin() + insertPos, addiInst);
                                insertPos++;
                            }
                        }
                    }
                    else if (movSrc->ot == BE::Operand::Type::IMMF32)
                    {
                        // 浮点立即数移动：需要特殊处理
                        // 这里简化处理，暂时使用伪指令，实际需要转换为浮点加载指令
                        auto* moveInst = BE::createMove(movDst, movSrc);
                        pred->insts.insert(pred->insts.begin() + insertPos, moveInst);
                    }
                    
                    // 清理临时创建的操作数对象
                    delete movSrc;
                    delete movDst;
                }

                // 删除 phi 指令
                BE::MInstruction::delInst(insts[idx]);
                insts.erase(insts.begin() + idx);
            }
        }
        
        // 额外步骤：遍历整个函数，消解其他可能存在的Move伪指令
        eliminateMoveInstructions(func);
    }
    
    void PhiEliminationPass::eliminateMoveInstructions(BE::Function* func)
    {
        // 遍历函数中的所有基本块
        for (auto& [bid, block] : func->blocks)
        {
            auto& insts = block->insts;
            
            // 遍历基本块中的每条指令
            for (size_t i = 0; i < insts.size(); ++i)
            {
                // 检查是否是Move指令
                if (auto* moveInst = dynamic_cast<BE::MoveInst*>(insts[i]))
                {
                    // 获取源和目标操作数
                    BE::Operand* src = moveInst->src;
                    BE::Operand* dst = moveInst->dest;
                    
                    if (!src || !dst) 
                    {
                        ERROR("Move instruction has null source or destination");
                        continue;
                    }
                    
                    // 根据操作数类型转换为实际的RISC-V指令
                    BE::MInstruction* newInst = nullptr;
                    
                    if (src->ot == BE::Operand::Type::REG && dst->ot == BE::Operand::Type::REG)
                    {
                        // 寄存器到寄存器的移动
                        auto* srcReg = static_cast<BE::RegOperand*>(src);
                        auto* dstReg = static_cast<BE::RegOperand*>(dst);
                        
                        // 使用 addi rd, rs, 0
                        newInst = BE::RV64::createIInst(
                            BE::RV64::Operator::ADDI,
                            dstReg->reg,
                            srcReg->reg,
                            0
                        );
                    }
                    else if (src->ot == BE::Operand::Type::IMMI32 && dst->ot == BE::Operand::Type::REG)
                    {
                        // 立即数到寄存器的移动
                        auto* immOp = static_cast<BE::I32Operand*>(src);
                        auto* dstReg = static_cast<BE::RegOperand*>(dst);
                        
                        int32_t imm = immOp->val;
                        
                        if (imm >= -2048 && imm <= 2047)
                        {
                            // 小立即数：addi rd, x0, imm
                            newInst = BE::RV64::createIInst(
                                BE::RV64::Operator::ADDI,
                                dstReg->reg,
                                BE::RV64::PR::x0,
                                imm
                            );
                        }
                        else
                        {
                            // 大立即数：需要多指令序列
                            // 这里简化处理，创建伪指令，实际应该插入多条指令
                            // 注意：这会改变指令列表大小，需要特殊处理
                            // 暂时保留原Move指令
                            continue;
                        }
                    }
                    
                    // 如果成功创建了新指令，替换原Move指令
                    if (newInst)
                    {
                        // 删除原Move指令
                        BE::MInstruction::delInst(insts[i]);
                        // 替换为新指令
                        insts[i] = newInst;
                    }
                }
            }
        }
    }
}  // namespace BE::RV64::Passes::Lowering
