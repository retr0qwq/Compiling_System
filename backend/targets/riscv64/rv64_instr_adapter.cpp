#include <backend/targets/riscv64/rv64_instr_adapter.h>
#include <backend/targets/riscv64/rv64_defs.h>
#include <algorithm>

namespace BE::Targeting::RV64
{
    using namespace BE::RV64;

    bool InstrAdapter::isCall(BE::MInstruction* inst) const { 
        // TODO("判断是否为调用指令"); 
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return false;
        return ri->op == Operator::CALL;
    }

    bool InstrAdapter::isReturn(BE::MInstruction* inst) const { 
        // TODO("判断是否为返回指令"); 
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return false;
        // RV64 RET 指令
        return ri->op == Operator::RET;
    }

    bool InstrAdapter::isUncondBranch(BE::MInstruction* inst) const { 
        // TODO("判断是否为无条件跳转指令"); 
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return false;
        // 无条件跳转在 RISC-V 是 JAL 到 x0 或者 JAL 指令
        return ri->op == Operator::JAL && ri->rd == Register(0); // rd = x0 表示无条件跳
    }

    bool InstrAdapter::isCondBranch(BE::MInstruction* inst) const { 
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return false;

        // 条件跳转 B 类型
        switch (ri->op)
        {
            case Operator::BEQ:
            case Operator::BNE:
            case Operator::BLT:
            case Operator::BGE:
            case Operator::BLTU:
            case Operator::BGEU:
            case Operator::BGT:
            case Operator::BLE:
            case Operator::BGTU:
            case Operator::BLEU:
                return true;
            default:
                return false;
        }
    }

    int InstrAdapter::extractBranchTarget(BE::MInstruction* inst) const { 
        // TODO("从分支指令中提取目标基本块标签 ID"); 
         if (!inst) return -1;
        // 只处理 PseudoInst
        auto* pi = dynamic_cast<BE::PseudoInst*>(inst);
        if (!pi) return -1;

        const std::string& c = pi->comment;

        // 无条件跳转: "br L<ID>"
        if (c.substr(0, 2) == "br")
        {
            auto pos = c.find('L');
            if (pos != std::string::npos)
            {
                // 提取数字
                try {
                    int labelId = std::stoi(c.substr(pos + 1));
                    return labelId;
                } catch (...) {
                    return -1;
                }
            }
        }

        // 条件跳转: "brcond rX, L<trueId>, L<falseId>"
        if (c.substr(0, 6) == "brcond")
        {
            // 查找第一个 L
            auto pos = c.find('L');
            if (pos != std::string::npos)
            {
                try {
                    int labelId = std::stoi(c.substr(pos + 1));
                    return labelId; // 返回 True 分支 ID
                } catch (...) {
                    return -1;
                }
            }
        }

        return -1; // 非跳转指令返回 -1
    }

    void InstrAdapter::enumUses(BE::MInstruction* inst, std::vector<BE::Register>& out) const
    {
        // TODO("统计指令使用的寄存器，存入vector out中");
        if (!inst) return;

        if (auto* ri = dynamic_cast<Instr*>(inst))
        {
            // 根据类型不同列出源寄存器
            switch (ri->op)
            {
                case Operator::ADD:
                case Operator::SUB:
                case Operator::MUL:
                case Operator::DIV:
                case Operator::AND:
                case Operator::OR:
                case Operator::XOR:
                case Operator::SLT:
                case Operator::SLTU:
                case Operator::SLL:
                case Operator::SRL:
                case Operator::SRA:
                case Operator::FEQ_S:
                case Operator::FLT_S:
                case Operator::FLE_S:
                    out.push_back(ri->rs1);
                    out.push_back(ri->rs2);
                    break;

                case Operator::ADDI:
                case Operator::SLTI:
                case Operator::JALR:
                    out.push_back(ri->rs1);
                    break;

                case Operator::BEQ:
                case Operator::BNE:
                case Operator::BLT:
                case Operator::BGE:
                case Operator::BLTU:
                case Operator::BGEU:
                    out.push_back(ri->rs1);
                    out.push_back(ri->rs2);
                    break;

                default:
                    break;
            }
        }
    }

    void InstrAdapter::enumDefs(BE::MInstruction* inst, std::vector<BE::Register>& out) const
    {
        // TODO("统计指令定义的寄存器，存入vector out中(可能为空集)");
        if (!inst) return;

        if (auto* ri = dynamic_cast<Instr*>(inst))
        {
            switch (ri->op)
            {
                case Operator::ADD:
                case Operator::SUB:
                case Operator::MUL:
                case Operator::DIV:
                case Operator::AND:
                case Operator::OR:
                case Operator::XOR:
                case Operator::SLT:
                case Operator::SLTU:
                case Operator::SLL:
                case Operator::SRL:
                case Operator::SRA:
                case Operator::FEQ_S:
                case Operator::FLT_S:
                case Operator::FLE_S:
                case Operator::ADDI:
                case Operator::SLTI:
                case Operator::JALR:
                    out.push_back(ri->rd);
                    break;

                case Operator::CALL:
                    out.push_back(ri->rd); // 调用结果寄存器
                    break;

                default:
                    break;
            }
        }
    }

    static void replaceReg(BE::Register& slot, const BE::Register& from, const BE::Register& to)
    {
        if (slot == from) slot = to;
    }

    void InstrAdapter::replaceUse(BE::MInstruction* inst, const BE::Register& from, const BE::Register& to) const
    {
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return;
        replaceReg(ri->rs1, from, to);
        replaceReg(ri->rs2, from, to);
    }

    void InstrAdapter::replaceDef(BE::MInstruction* inst, const BE::Register& from, const BE::Register& to) const
    {
        auto* ri = dynamic_cast<Instr*>(inst);
        if (!ri) return;
        replaceReg(ri->rd, from, to);
    }

    void InstrAdapter::enumPhysRegs(BE::MInstruction* inst, std::vector<BE::Register>& out) const
    {
        if (!inst) return;

        // 如果是真实机器指令，假设有 rd, rs1, rs2
        if (auto* ri = dynamic_cast<Instr*>(inst))
        {
            if (!ri->rd.isVreg)  out.push_back(ri->rd);
            if (!ri->rs1.isVreg) out.push_back(ri->rs1);
            if (!ri->rs2.isVreg) out.push_back(ri->rs2);
            return;
        }

        // FILoadInst: 目标寄存器是物理寄存器
        if (auto* li = dynamic_cast<BE::FILoadInst*>(inst))
        {
            if (!li->dest.isVreg) out.push_back(li->dest);
            return;
        }

        // FIStoreInst: 源寄存器是物理寄存器
        if (auto* si = dynamic_cast<BE::FIStoreInst*>(inst))
        {
            if (!si->src.isVreg) out.push_back(si->src);
            return;
        }

        // MoveInst: 取 src/dest，如果是寄存器 Operand，可以扩展
        if (auto* mi = dynamic_cast<BE::MoveInst*>(inst))
        {
            if (auto* rdst = dynamic_cast<BE::RegOperand*>(mi->dest))
                if (!rdst->reg.isVreg) out.push_back(rdst->reg);

            if (auto* rsrc = dynamic_cast<BE::RegOperand*>(mi->src))
                if (!rsrc->reg.isVreg) out.push_back(rsrc->reg);
            return;
        }

        // PhiInst: resReg 是物理寄存器
        if (auto* phi = dynamic_cast<BE::PhiInst*>(inst))
        {
            if (!phi->resReg.isVreg) out.push_back(phi->resReg);
            return;
        }
        
    }
    void BE::Targeting::RV64::InstrAdapter::insertReloadBefore(
    BE::Block* block,
    std::deque<BE::MInstruction*>::iterator it,
    const BE::Register& physReg,
    int frameIndex) const
    {
        if (!block) return;

        BE::MInstruction* reload = nullptr;

        // 根据寄存器类型选择加载指令
        if (physReg.dt && physReg.dt->dt == BE::DataType::Type::FLOAT) {
            // 浮点寄存器，使用 FLW / FLD 根据长度
            if (physReg.dt->dl == BE::DataType::Length::B32)
                reload = new BE::FILoadInst(physReg, frameIndex, "reload FLW");
            else
                reload = new BE::FILoadInst(physReg, frameIndex, "reload FLD");
        } else {
            // 整数寄存器，使用 LW / LD 根据长度
            if (physReg.dt && physReg.dt->dl == BE::DataType::Length::B32)
                reload = new BE::FILoadInst(physReg, frameIndex, "reload LW");
            else
                reload = new BE::FILoadInst(physReg, frameIndex, "reload LD");
        }

        // 插入到迭代器指向位置之前
        block->insts.insert(it, reload);
    }

    void InstrAdapter::insertSpillAfter(
    BE::Block* block,
    std::deque<BE::MInstruction*>::iterator it,
    const BE::Register& physReg,
    int frameIndex) const
    {
        if (!block) return;

        BE::MInstruction* spill = nullptr;

        if (physReg.dt &&  physReg.dt->dt == DataType::Type::FLOAT)
        {
            spill = new BE::FIStoreInst(physReg, frameIndex, "spill float reg");
        }
        else
        {
            spill = new BE::FIStoreInst(physReg, frameIndex, "spill int reg");
        }

        // 插入到 it 之后
        if (it != block->insts.end())
            block->insts.insert(std::next(it), spill);
        else
            block->insts.push_back(spill);
    }
}  // namespace BE::Targeting::RV64
