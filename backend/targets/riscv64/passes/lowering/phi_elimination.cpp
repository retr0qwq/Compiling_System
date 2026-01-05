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

                    // 根据 srcOp 类型构造合适的操作数并插入 move dest <- src
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

                    pred->insts.insert(pred->insts.begin() + insertPos, BE::createMove(movDst, movSrc));
                    // 将插入点后移，保持后续插入顺序
                    insertPos++;
                }

                // 删除 phi 指令
                BE::MInstruction::delInst(insts[idx]);
                insts.erase(insts.begin() + idx);
            }
        }
    }
}  // namespace BE::RV64::Passes::Lowering
