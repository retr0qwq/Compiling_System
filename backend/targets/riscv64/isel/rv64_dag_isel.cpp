#include <backend/targets/riscv64/isel/rv64_dag_isel.h>
#include <backend/target/target.h>
#include <backend/dag/selection_dag.h>
#include <backend/dag/isd.h>
#include <backend/dag/dag_builder.h>
#include <backend/targets/riscv64/dag/rv64_dag_legalize.h>
#include <backend/targets/riscv64/rv64_defs.h>
#include <backend/targets/riscv64/rv64_reg_info.h>
#include <middleend/module/ir_instruction.h>
#include <middleend/module/ir_function.h>
#include <debug.h>
#include <transfer.h>
#include <queue>
#include <functional>

namespace BE::RV64
{
    [[maybe_unused]]static inline bool imm12(int imm) { return imm >= -2048 && imm <= 2047; }

    std::vector<const DAG::SDNode*> DAGIsel::scheduleDAG(const DAG::SelectionDAG& dag)
    {
        // ============================================================================
        // TODO: 实现 DAG 调度
        // ============================================================================
        //
        // 作用：
        // 将 DAG 的所有节点排序为线性指令序列，保证依赖关系正确。
        //
        // 为什么需要：
        // - DAG 是无序的节点集合，生成代码前必须确定指令的先后顺序
        // - 必须保证每条指令的操作数在使用前已被计算（拓扑序）
        // - 需要正确处理 Chain 依赖，维持内存操作与副作用的顺序
        //
        // 如何做：
        // - 后序遍历：从根节点（无使用者的节点）出发，先访问依赖再访问当前节点

        // TODO("实现 DAG 调度：输出拓扑序的节点列表");
        std::vector<const DAG::SDNode*> result;
        std::set<const DAG::SDNode*> visited;

        // 内部递归函数，调度单个节点
        std::function<void(const DAG::SDNode*)> visitNode = [&](const DAG::SDNode* node) {
            if (!node || visited.count(node)) return;

            // 先调度 value operands
            for (unsigned i = 0; i < node->getNumOperands(); ++i)
            {
                const auto& op = node->getOperand(i);
                if (!op) continue;

                bool isChainOperand = false;

                if (op.getNode()->getNumValues() > 1)  // 如果节点有 chain 输出
                {
                    // 判断该 operand 是否 chain 类型
                    if (op.getResNo() == 1) isChainOperand = true;
                }

                if (!isChainOperand)
                    visitNode(op.getNode());
            }

            // 再调度 chain operand
            for (unsigned i = 0; i < node->getNumOperands(); ++i)
            {
                const auto& op = node->getOperand(i);
                if (!op) continue;

                bool isChainOperand = false;
                if (op.getNode()->getNumValues() > 1 && op.getResNo() == 1)
                    isChainOperand = true;

                if (isChainOperand)
                    visitNode(op.getNode());
            }

            // 当前节点加入调度结果
            visited.insert(node);
            result.push_back(node);
        };

        // 遍历 DAG 所有节点
        for (auto* n : dag.getNodes())
            visitNode(n);

        return result;
    }

    void DAGIsel::allocateRegistersForNode(const DAG::SDNode* node)
    {
        // ============================================================================
        // 为调度后的 DAG 节点预分配虚拟寄存器
        // ============================================================================
        //
        // 为什么需要：
        // - 在指令选择前，先为每个计算结果分配虚拟寄存器
        // - 确保跨基本块的值（如 PHI 操作数）使用一致的寄存器映射
        // - 分离"分配"与"使用"两个阶段，简化后续的指令生成逻辑
        //
        // 策略：
        // - 若节点对应 IR 寄存器，复用 IR 寄存器映射
        // - 否则分配临时虚拟寄存器
        // - 常量、LABEL、SYMBOL 等叶子节点按需实例化，无需预分配

        if (node->getNumValues() == 0) return;

        auto opcode = static_cast<DAG::ISD>(node->getOpcode());

        if (opcode == DAG::ISD::LABEL || opcode == DAG::ISD::SYMBOL || opcode == DAG::ISD::CONST_I32 ||
            opcode == DAG::ISD::CONST_I64 || opcode == DAG::ISD::CONST_F32 || opcode == DAG::ISD::FRAME_INDEX)
            return;

        BE::DataType* dt = node->getValueType(0);
        Register      vreg;

        if (node->hasIRRegId())
            vreg = getOrCreateVReg(node->getIRRegId(), dt);
        else
            vreg = getVReg(dt);

        nodeToVReg_[node] = vreg;
    }

    Register DAGIsel::getOperandReg(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // 操作数获取：统一的实例化入口
        // ============================================================================
        //
        // 作用：为 DAG 节点返回或实例化对应的寄存器
        //
        // 为什么需要：
        // - 指令选择时，需要将 DAG 节点（抽象）映射到寄存器（具体）
        // - 常量、地址节点在首次使用时才生成指令，这可以避免为未使用的常量生成无用指令
        // - 统一处理已分配寄存器、IR 寄存器映射、按需实例化三种情况

        if (!node) ERROR("Cannot get register for null node");

        auto opcode = static_cast<DAG::ISD>(node->getOpcode());

        auto it = nodeToVReg_.find(node);
        if (it != nodeToVReg_.end()) return it->second;

        if (opcode == DAG::ISD::REG && node->hasIRRegId())
            return getOrCreateVReg(node->getIRRegId(), node->getNumValues() > 0 ? node->getValueType(0) : BE::I64);

        if (opcode == DAG::ISD::CONST_I32 || opcode == DAG::ISD::CONST_I64)
        {
            DataType* dt      = (opcode == DAG::ISD::CONST_I32) ? BE::I32 : BE::I64;
            Register  destReg = getVReg(dt);
            int64_t   imm     = node->hasImmI64() ? node->getImmI64() : 0;

            m_block->insts.push_back(createMove(new RegOperand(destReg), static_cast<int>(imm), LOC_STR));

            nodeToVReg_[node] = destReg;
            return destReg;
        }

        if (opcode == DAG::ISD::CONST_F32)
        {
            Register destReg = getVReg(BE::F32);

            if (node->hasImmF32())
            {
                float    f_val = node->getImmF32();
                uint32_t bits;
                memcpy(&bits, &f_val, sizeof(float));
                Register tempReg = getVReg(BE::I32);
                m_block->insts.push_back(createMove(new RegOperand(tempReg), static_cast<int>(bits), LOC_STR));
                m_block->insts.push_back(createR2Inst(Operator::FMV_W_X, destReg, tempReg));
            }

            nodeToVReg_[node] = destReg;
            return destReg;
        }

        if (opcode == DAG::ISD::FRAME_INDEX || opcode == DAG::ISD::SYMBOL) return materializeAddress(node, m_block);

        ERROR("Node not scheduled or cannot be materialized: %s",
            DAG::toString(static_cast<DAG::ISD>(node->getOpcode())));
        return Register();
    }

    Register DAGIsel::materializeAddress(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // 地址实例化：使用者负责实例化
        // ============================================================================
        //
        // 作用：将地址节点（FRAME_INDEX/SYMBOL）实例化为寄存器
        //
        // 为什么需要：
        // - 地址节点本身不生成独立的指令，而是由使用者（LOAD/STORE/ADD）决定如何实例化
        // - FRAME_INDEX 需要生成抽象的 FrameIndexOperand，由后续 Pass 替换为实际偏移
        // - SYMBOL 需要生成 LA 伪指令加载全局变量地址

        if (!node) ERROR("Cannot materialize null address");

        auto opcode = static_cast<DAG::ISD>(node->getOpcode());

        if (opcode == DAG::ISD::FRAME_INDEX && node->hasIRRegId())
        {
            size_t   ir_reg_id = node->getIRRegId();
            Register addrReg   = getVReg(BE::I64);

            Instr* addr_inst = createIInst(Operator::ADDI, addrReg, PR::sp, new FrameIndexOperand(ir_reg_id));
            m_block->insts.push_back(addr_inst);

            return addrReg;
        }

        if (opcode == DAG::ISD::SYMBOL && node->hasSymbol())
        {
            Register addrReg = getVReg(BE::I64);
            Label    symbolLabel(node->getSymbol(), false, true);
            m_block->insts.push_back(createUInst(Operator::LA, addrReg, symbolLabel));
            return addrReg;
        }

        auto it = nodeToVReg_.find(node);
        if (it != nodeToVReg_.end()) return it->second;

        if (opcode == DAG::ISD::REG && node->hasIRRegId())
            return getOrCreateVReg(node->getIRRegId(), node->getNumValues() > 0 ? node->getValueType(0) : BE::I64);

        ERROR("Cannot materialize address for opcode: %s", DAG::toString(opcode));
    }

    int DAGIsel::dataTypeSize(BE::DataType* dt)
    {
        if (dt == BE::I32 || dt == BE::F32) return 4;
        if (dt == BE::I64 || dt == BE::F64 || dt == BE::PTR) return 8;
        return 4;
    }

    Register DAGIsel::getOrCreateVReg(size_t ir_reg_id, BE::DataType* dt)
    {
        auto it = ctx_.vregMap.find(ir_reg_id);
        if (it != ctx_.vregMap.end())
        {
            if (it->second.dt == dt) return it->second;

            // 如果进入到这个分支，说明类型不匹配
            // 这个问题在 ARM 中需要插入类型转化
            // 但 RISC-V 中对寄存器宽度没有要求，所以这里直接返回也可以
            return it->second;
        }

        Register vreg           = getVReg(dt);
        ctx_.vregMap[ir_reg_id] = vreg;
        return vreg;
    }

    void DAGIsel::importGlobals()
    {
        // ============================================================================
        // TODO: 导入全局变量
        // ============================================================================
        //
        // 作用：
        // 将 IR 模块中的全局变量转换为后端的 GlobalVariable 对象。
        //
        // 为什么需要：
        // - 全局变量需在生成的汇编中声明和初始化
        // - 需转换类型（ME::DataType → BE::DataType）
        // - 需处理初始化值（标量 vs 数组）
        //
        // 关键点：
        // - 遍历 ir_module_->globalVars
        // - 创建 BE::GlobalVariable 对象
        // - 处理数组维度（arrayDims）与初始值（initList/init）
        // - 浮点数需位转换（FLOAT_TO_INT_BITS）

        // TODO("导入全局变量到后端模块");
        for (auto* gv : ir_module_->globalVars)
        {
            if (!gv) continue;
            BE::DataType* beType = nullptr;
            switch (gv->dt)
            {
                case ME::DataType::I32: beType = BE::I32; break;
                case ME::DataType::I64: beType = BE::I64; break;
                case ME::DataType::F32: beType = BE::F32; break;
                default:
                    ERROR("Unsupported global variable type");
            }

            auto* bGV = new BE::GlobalVariable(beType, gv->name);
            // 初始化值（放入 initVals）
            if (gv->init)
            {
                if (gv->dt == ME::DataType::I32 || gv->dt == ME::DataType::I64)
                {
                    bGV->initVals.push_back(
                        static_cast<ME::ImmeI32Operand*>(gv->init)->value
                    );
                }
                else if (gv->dt == ME::DataType::F32)
                {
                    int bits = FLOAT_TO_INT_BITS(
                        static_cast<ME::ImmeF32Operand*>(gv->init)->value
                    );
                    bGV->initVals.push_back(bits);
                }
            }
            else
            {
                // 无初始化 → 默认 0
                bGV->initVals.push_back(0);
            }
            m_backend_module->globals.push_back(bGV);
        }
    }

    void DAGIsel::collectAllocas(ME::Function* ir_func)
    {
        // ============================================================================
        // TODO: 收集函数中的所有 alloca 并注册到 frameInfo
        // ============================================================================
        //
        // 作用：
        // 遍历函数的所有 IR 指令，找到所有 ALLOCA 指令，计算其需要的栈空间大小，
        // 并在函数级别的栈帧管理中为其分配槽位。

        // TODO("收集 alloca 并注册到 frameInfo");
        ctx_.mfunc->frameInfo.clear();
        ctx_.allocaFI.clear();  // 你之前留的表，现在其实可以不用

        for (auto& [bid, block] : ir_func->blocks)
        {
            for (auto* inst : block->insts)
            {
                if (inst->opcode != ME::Operator::ALLOCA)
                    continue;

                auto* ai = static_cast<ME::AllocaInst*>(inst);
                size_t irRegId = ai->res->getRegNum();

                // 计算需要的字节数
                int sizeBytes = dataTypeSize(mapType(ai->dt));
                int alignment = 16; 
                //  注册为 LocalVar
                ctx_.mfunc->frameInfo.createLocalObject(
                    irRegId,
                    sizeBytes,
                    alignment
                );
            }
        }
    }
    void DAGIsel::collectCall(ME::Function* ir_func)
    {
        int maxOutgoingBytes = 0;

    for (auto& [bid, block] : ir_func->blocks)
    {
        for (auto* inst : block->insts)
        {
            if (inst->opcode != ME::Operator::CALL)
                continue;

            auto* call = static_cast<ME::CallInst*>(inst);

            int intCnt   = 0;
            int floatCnt = 0;

            // 统计参数类型
            for (auto& [argType, argOp] : call->args)
            {
                if (argType == ME::DataType::F32)
                    floatCnt++;
                else
                    intCnt++;
            }

            // RV64 ABI：前 8 个进寄存器
            int intOverflow   = std::max(0, intCnt   - 8);
            int floatOverflow = std::max(0, floatCnt - 8);

            int bytes = (intOverflow + floatOverflow) * 8;

            maxOutgoingBytes = std::max(maxOutgoingBytes, bytes);
        }
    }

    if (maxOutgoingBytes > 0)
    {
        ctx_.mfunc->frameInfo.setParamAreaSize(maxOutgoingBytes);
    }
    }
    void DAGIsel::setupParameters(ME::Function* ir_func)
    {
        // ============================================================================
        // TODO: 为函数参数创建虚拟寄存器
        // ============================================================================
        //
        // 作用：
        // 遍历 IR 函数定义中的所有参数，为每个参数分配虚拟寄存器，并记录参数的虚拟寄存器映射关系

        // TODO("为函数参数创建虚拟寄存器并建立映射");

        auto& args = ir_func->funcDef->argRegs;

        for (auto& [argTy, argOp] : args)
        {
            // IR 参数的 SSA reg id
            size_t irRegId = argOp->getRegNum();
            // IR 类型 -> 后端类型
            BE::DataType* beTy = mapType(argTy);
            // 为参数分配虚拟寄存器
            Register vreg = getOrCreateVReg(irRegId, beTy);
            // 记录到函数级映射
            ctx_.vregMap[irRegId] = vreg;
        }
    }

    void DAGIsel::selectCopy(const DAG::SDNode* node, BE::Block* m_block)
    {
        if (node->getNumOperands() < 1) return;

        const DAG::SDNode* src = node->getOperand(0).getNode();
        if (!src) return;

        Register dst    = getOperandReg(node, m_block);
        Register srcReg = getOperandReg(src, m_block);

        m_block->insts.push_back(createMove(new RegOperand(dst), new RegOperand(srcReg), LOC_STR));
    }

    void DAGIsel::selectPhi(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择 PHI 节点
        // ============================================================================
        //
        // 作用：
        // 为 PHI 节点生成 MIR 的 PhiInst，记录所有前驱块与对应的值。
        //
        // 为什么需要：
        // - PHI 节点在 SSA 中合并来自不同前驱的值
        // - 需要保留前驱块信息，供后续 PHI 消解 Pass 使用
        //
        // 关键点：
        // - 此处的常量应直接作为立即数，无需实例化为寄存器
        // - 至于为什么，你可以思考一下 getOperandReg 的实现
        // - getOperandReg 对于第一次使用常量的行为是什么，会将立即数加载的指令插入到什么地方？

        // TODO("选择 PHI 节点：提取前驱与值，生成 PhiInst");
        size_t irRegId = node->getIRRegId();
        BE::DataType* dt = node->getValueType(0);

        Register dst = getOrCreateVReg(irRegId, dt);

        // -----------------------------------------
        // 2. 创建 MIR PhiInst
        // -----------------------------------------
        auto* phi = new BE::PhiInst(dst);

        // -----------------------------------------
        // 3. 解析 DAG PHI 的操作数
        //    operands = [LABEL0, VAL0, LABEL1, VAL1, ...]
        // -----------------------------------------
        const auto& ops = node->getOperands();
         for (size_t i = 0; i < ops.size(); i += 2)
    {
        const DAG::SDNode* labelNode = ops[i].getNode();
        const DAG::SDNode* valNode   = ops[i + 1].getNode();

        uint32_t label = static_cast<uint32_t>(labelNode->getImmI64());

        BE::Operand* srcOp = nullptr;
        (void)label; 
        (void)srcOp; 
        // -----------------------------------------
        // 3. PHI incoming value 的 Operand 化
        // -----------------------------------------
        if (valNode->hasIRRegId())
        {
            Register srcReg = getOrCreateVReg(
                valNode->getIRRegId(),
                valNode->getValueType(0)
            );
            srcOp = new BE::RegOperand(srcReg);
        }
        else if (valNode->hasImmI64())
        {
            Register srcReg = getOperandReg(valNode, m_block);
            srcOp = new BE::RegOperand(srcReg);
        }
        else if (valNode->hasFrameIndex())
        {
            srcOp = new BE::FrameIndexOperand(valNode->getFrameIndex());
        }
        else
        {
            ERROR("Unsupported PHI incoming value");
        }

        // -----------------------------------------
        // 4. 插入到 block 的 PHI 区
        // -----------------------------------------
        m_block->insts.push_front(phi);

        selected_.insert(node);
    }
}
    void DAGIsel::selectBinary(const DAG::SDNode* node, BE::Block* m_block)
    {
        if (node->getNumOperands() < 2) return;

        auto opcode = static_cast<DAG::ISD>(node->getOpcode());

        Register dst = nodeToVReg_.at(node);

        const DAG::SDNode* lhs = node->getOperand(0).getNode();
        const DAG::SDNode* rhs = node->getOperand(1).getNode();

        Register lhsReg;
        auto     lhsOp = static_cast<DAG::ISD>(lhs->getOpcode());

        bool isAllocaReg = false;
        int  allocaFI    = -1;
        if (lhsOp == DAG::ISD::REG && lhs->hasIRRegId())
        {
            auto it = ctx_.allocaFI.find(lhs->getIRRegId());
            if (it != ctx_.allocaFI.end())
            {
                isAllocaReg = true;
                allocaFI    = it->second;
            }
        }

        if (lhsOp == DAG::ISD::SYMBOL)
            lhsReg = materializeAddress(lhs, m_block);
        else if (lhsOp == DAG::ISD::FRAME_INDEX || isAllocaReg)
        {
            lhsReg            = getVReg(BE::I64);
            int    fi         = isAllocaReg ? allocaFI : lhs->getFrameIndex();
            Instr* addrInst   = createIInst(Operator::ADDI, lhsReg, PR::sp, 0);
            addrInst->fiop    = new FrameIndexOperand(fi);
            addrInst->use_ops = true;
            m_block->insts.push_back(addrInst);
        }
        else
            lhsReg = getOperandReg(lhs, m_block);

        Register rhsReg;
        int      rhsImm     = 0;
        bool     isRhsConst = false;

        auto rhsOp = static_cast<DAG::ISD>(rhs->getOpcode());
        if (rhsOp == DAG::ISD::CONST_I32 && rhs->hasImmI64())
        {
            rhsImm     = static_cast<int>(rhs->getImmI64());
            isRhsConst = true;
        }
        else
            rhsReg = getOperandReg(rhs, m_block);

        Operator op;
        bool     isFloat =
            (node->getNumValues() > 0 && (node->getValueType(0) == BE::F32 || node->getValueType(0) == BE::F64));
        bool is32bit = (dst.dt == BE::I32);

        switch (opcode)
        {
            case DAG::ISD::ADD: op = isFloat ? Operator::FADD_S : (is32bit ? Operator::ADDW : Operator::ADD); break;
            case DAG::ISD::SUB: op = isFloat ? Operator::FSUB_S : (is32bit ? Operator::SUBW : Operator::SUB); break;
            case DAG::ISD::MUL: op = isFloat ? Operator::FMUL_S : (is32bit ? Operator::MULW : Operator::MUL); break;
            case DAG::ISD::DIV: op = isFloat ? Operator::FDIV_S : (is32bit ? Operator::DIVW : Operator::DIV); break;
            case DAG::ISD::FADD: op = Operator::FADD_S; break;
            case DAG::ISD::FSUB: op = Operator::FSUB_S; break;
            case DAG::ISD::FMUL: op = Operator::FMUL_S; break;
            case DAG::ISD::FDIV: op = Operator::FDIV_S; break;
            case DAG::ISD::MOD: op = is32bit ? Operator::REMW : Operator::REM; break;
            case DAG::ISD::AND: op = Operator::AND; break;
            case DAG::ISD::OR: op = Operator::OR; break;
            case DAG::ISD::XOR: op = Operator::XOR; break;
            case DAG::ISD::SHL: op = Operator::SLL; break;
            case DAG::ISD::ASHR: op = Operator::SRA; break;
            case DAG::ISD::LSHR: op = Operator::SRL; break;
            default: ERROR("Unsupported binary operator: %d", node->getOpcode()); return;
        }

        if (isRhsConst)
        {
            bool     is32bit = (dst.dt == BE::I32);
            Operator iop;
            bool     hasImmForm = true;

            switch (op)
            {
                case Operator::ADD: iop = is32bit ? Operator::ADDIW : Operator::ADDI; break;
                case Operator::AND: iop = Operator::ANDI; break;
                case Operator::OR: iop = Operator::ORI; break;
                case Operator::XOR: iop = Operator::XORI; break;
                case Operator::SLL: iop = is32bit ? Operator::SLLIW : Operator::SLLI; break;
                case Operator::SRA: iop = is32bit ? Operator::SRAIW : Operator::SRAI; break;
                case Operator::SRL: iop = is32bit ? Operator::SRLIW : Operator::SRLI; break;
                default: hasImmForm = false; break;
            }

            if (hasImmForm)
                m_block->insts.push_back(createIInst(iop, dst, lhsReg, rhsImm));
            else
            {
                Register tmpReg = getVReg(lhsReg.dt);
                m_block->insts.push_back(createMove(new RegOperand(tmpReg), rhsImm, LOC_STR));
                m_block->insts.push_back(createRInst(op, dst, lhsReg, tmpReg));
            }
        }
        else
            m_block->insts.push_back(createRInst(op, dst, lhsReg, rhsReg));
    }

    void DAGIsel::selectUnary(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择一元运算节点（可选）
        // ============================================================================
        //
        // 说明：
        // 一元运算（如 NEG、NOT）在基础 DAG 中较少使用。
        // 若你的 IR 或优化中产生了一元节点，可在此处理。
        //
        // TODO("可选：处理一元运算（NEG/NOT 等）");
        (void)node;  
        (void)m_block;
    }

    bool DAGIsel::selectAddress(const DAG::SDNode* addrNode, const DAG::SDNode*& baseNode, int64_t& offset)
    {
        if (!addrNode) return false;

        auto opcode = static_cast<DAG::ISD>(addrNode->getOpcode());

        if (opcode == DAG::ISD::FRAME_INDEX || opcode == DAG::ISD::SYMBOL)
        {
            baseNode = addrNode;
            offset   = 0;
            return true;
        }

        if (opcode == DAG::ISD::ADD)
        {
            const DAG::SDNode* lhs = addrNode->getOperand(0).getNode();
            const DAG::SDNode* rhs = addrNode->getOperand(1).getNode();

            const DAG::SDNode* lhsBase;
            int64_t            lhsOffset = 0;
            if (selectAddress(lhs, lhsBase, lhsOffset))
            {
                if ((static_cast<DAG::ISD>(rhs->getOpcode()) == DAG::ISD::CONST_I32 ||
                        static_cast<DAG::ISD>(rhs->getOpcode()) == DAG::ISD::CONST_I64) &&
                    rhs->hasImmI64())
                {
                    baseNode = lhsBase;
                    offset   = lhsOffset + rhs->getImmI64();
                    return true;
                }
                return false;
            }

            const DAG::SDNode* rhsBase;
            int64_t            rhsOffset = 0;
            if (selectAddress(rhs, rhsBase, rhsOffset))
            {
                if ((static_cast<DAG::ISD>(lhs->getOpcode()) == DAG::ISD::CONST_I32 ||
                        static_cast<DAG::ISD>(lhs->getOpcode()) == DAG::ISD::CONST_I64) &&
                    lhs->hasImmI64())
                {
                    baseNode = rhsBase;
                    offset   = rhsOffset + lhs->getImmI64();
                    return true;
                }
                return false;
            }

            return false;
        }

        return false;
    }

    void DAGIsel::selectLoad(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // 选择 LOAD 节点, 作为示例实现，仅供参考
        // ============================================================================
        //
        // 作用：
        // 为 LOAD 节点生成目标相关的访存指令（LW/LD/FLW/FLD）。
        //
        // 为什么需要地址选择：
        // - 地址可能是简单的 [base + offset]，也可能是复杂表达式
        // - 声明式地址选择（selectAddress）可将常见模式折叠到访存指令的立即数字段
        // - 若地址过于复杂，需先完整计算到寄存器

        if (node->getNumOperands() < 2) return;

        Register           dst  = nodeToVReg_.at(node);
        const DAG::SDNode* addr = node->getOperand(1).getNode();

        const DAG::SDNode* baseNode;
        int64_t            offset = 0;

        if (selectAddress(addr, baseNode, offset))
        {
            Register baseReg;

            if (static_cast<DAG::ISD>(baseNode->getOpcode()) == DAG::ISD::FRAME_INDEX)
            {
                int fi            = baseNode->getFrameIndex();
                baseReg           = getVReg(BE::I64);
                Instr* addrInst   = createIInst(Operator::ADDI, baseReg, PR::sp, 0);
                addrInst->fiop    = new FrameIndexOperand(fi);
                addrInst->use_ops = true;
                m_block->insts.push_back(addrInst);
            }
            else if (static_cast<DAG::ISD>(baseNode->getOpcode()) == DAG::ISD::SYMBOL && baseNode->hasSymbol())
            {
                std::string symbol = baseNode->getSymbol();
                baseReg            = getVReg(BE::I64);
                Label symbolLabel(symbol, false, true);
                m_block->insts.push_back(createUInst(Operator::LA, baseReg, symbolLabel));
            }
            else
                baseReg = getOperandReg(baseNode, m_block);

            Operator loadOp = (dst.dt == BE::F32 || dst.dt == BE::F64) ? Operator::FLW : Operator::LW;

            if (offset < -2048 || offset > 2047)
            {
                Register offsetReg = getVReg(BE::I64);
                m_block->insts.push_back(createMove(new RegOperand(offsetReg), static_cast<int>(offset), LOC_STR));
                Register finalBase = getVReg(BE::I64);
                m_block->insts.push_back(createRInst(Operator::ADD, finalBase, baseReg, offsetReg));
                m_block->insts.push_back(createIInst(loadOp, dst, finalBase, 0));
            }
            else
                m_block->insts.push_back(createIInst(loadOp, dst, baseReg, static_cast<int>(offset)));
        }
        else
        {
            Register addrReg = getOperandReg(addr, m_block);
            Operator loadOp  = (dst.dt == BE::F32 || dst.dt == BE::F64) ? Operator::FLW : Operator::LW;
            m_block->insts.push_back(createIInst(loadOp, dst, addrReg, 0));
        }
    }

    void DAGIsel::selectStore(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择 STORE 节点
        // ============================================================================
        //
        // 作用：
        // 为 STORE 节点生成目标相关的存储指令（SW/SD/FSW/FSD）。
        //
        // 与 LOAD 的相似性：
        // - 同样需要地址选择与立即数范围检查
        // - 操作数：[Chain, Value, Address]
        // TODO("选择 STORE：地址折叠 + 生成存储指令");
        if (node->getNumOperands() < 3) return;

        const DAG::SDNode* valNode  = node->getOperand(1).getNode();
        const DAG::SDNode* addrNode = node->getOperand(2).getNode();

        Register valReg = getOperandReg(valNode, m_block);
        // 地址选择
        const DAG::SDNode* baseNode;
        int64_t            offset = 0;

        if (selectAddress(addrNode, baseNode, offset))
        {
            Register baseReg;

            if (static_cast<DAG::ISD>(baseNode->getOpcode()) == DAG::ISD::FRAME_INDEX)
            {
                int fi          = baseNode->getFrameIndex();
                baseReg         = getVReg(BE::I64);
                Instr* addrInst = createIInst(Operator::ADDI, baseReg, PR::sp, 0);
                addrInst->fiop  = new FrameIndexOperand(fi);
                addrInst->use_ops = true;
                m_block->insts.push_back(addrInst);
            }
            else if (static_cast<DAG::ISD>(baseNode->getOpcode()) == DAG::ISD::SYMBOL &&
                    baseNode->hasSymbol())
            {
                std::string symbol = baseNode->getSymbol();
                baseReg            = getVReg(BE::I64);
                Label symbolLabel(symbol, false, true);
                m_block->insts.push_back(createUInst(Operator::LA, baseReg, symbolLabel));
            }
            else
            {
                baseReg = getOperandReg(baseNode, m_block);
            }
            // 选择 STORE 指令
            Operator storeOp =
                (valReg.dt == BE::F32 || valReg.dt == BE::F64)
                    ? Operator::FSW
                    : Operator::SW;
            //  offset 是否能塞进立即数
            if (offset < -2048 || offset > 2047)
            {
                Register offsetReg = getVReg(BE::I64);
                m_block->insts.push_back(
                    createMove(new RegOperand(offsetReg),
                            static_cast<int>(offset),
                            LOC_STR));

                Register finalBase = getVReg(BE::I64);
                m_block->insts.push_back(
                    createRInst(Operator::ADD, finalBase, baseReg, offsetReg));

                m_block->insts.push_back(
                    createIInst(storeOp, valReg, finalBase, 0));
            }
            else
            {
                m_block->insts.push_back(
                    createIInst(storeOp, valReg, baseReg, static_cast<int>(offset)));
            }
        }
        else
        {
            // 地址无法折叠：直接用 addrReg
            Register addrReg = getOperandReg(addrNode, m_block);

            Operator storeOp =
                (valReg.dt == BE::F32 || valReg.dt == BE::F64)
                    ? Operator::FSW
                    : Operator::SW;

            m_block->insts.push_back(
                createIInst(storeOp, valReg, addrReg, 0));
        }
    }

    void DAGIsel::selectICmp(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择整数比较节点（ICMP）
        // ============================================================================

        // TODO("选择 ICMP：根据条件生成比较指令序列");
        Register dst = nodeToVReg_.at(node);
        BE::Register lhs = getOperandReg(node->getOperand(0).getNode(), m_block);
        BE::Register rhs = getOperandReg(node->getOperand(1).getNode(), m_block);

        CondCode cc = mapIcmpCond(node->getImmI64());

        switch (cc){
            case CondCode::EQ:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::SUB, tmp, lhs, rhs));
                m_block->insts.push_back(createIInst_impl(Operator::SLTIU, dst, tmp, 1, "icmp eq"));
                break;}
           case CondCode::NE:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::SUB, tmp, lhs, rhs));
                m_block->insts.push_back(createIInst_impl(Operator::SLTIU, dst, tmp, 1, "icmp eq"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, dst, 1, "icmp ne"));
                break;}
            case CondCode::LT:{
                m_block->insts.push_back(createRInst_impl(Operator::SLT, dst, lhs, rhs, "icmp lt"));
                break;}
            case CondCode::LE:{
                m_block->insts.push_back(createRInst_impl(Operator::SLT, dst, rhs, lhs, "icmp le"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, dst, 1, "icmp le"));
                break;}
            case CondCode::GT:{
                m_block->insts.push_back(createRInst_impl(Operator::SLT, dst, rhs, lhs, "icmp gt"));
                break;}
            case CondCode::GE:{
                m_block->insts.push_back(createRInst_impl(Operator::SLT, dst, lhs, rhs, "icmp ge"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, dst, 1, "icmp ge"));
                break;}
            case CondCode::ULT:{
                m_block->insts.push_back(createRInst_impl(Operator::SLTU, dst, lhs, rhs, "icmp ult"));
                break;}
            case CondCode::ULE:{
                m_block->insts.push_back(createRInst_impl(Operator::SLTU, dst, rhs, lhs, "icmp ule"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, dst, 1, "icmp ule"));
                break;}
            case CondCode::UGT:{
                m_block->insts.push_back(createRInst_impl(Operator::SLTU, dst, rhs, lhs, "icmp ugt"));
                break;}
            case CondCode::UGE:{
                m_block->insts.push_back(createRInst_impl(Operator::SLTU, dst, lhs, rhs, "icmp uge"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, dst, 1, "icmp uge"));
                break;}
            default:
                assert(false && "unsupported icmp cond");
        }
    }

    void DAGIsel::selectFCmp(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择浮点比较节点（FCMP）
        // ============================================================================

        // TODO("选择 FCMP：根据条件生成浮点比较指令");
        Register dst = nodeToVReg_.at(node);
        BE::Register lhs = getOperandReg(node->getOperand(0).getNode(), m_block);
        BE::Register rhs = getOperandReg(node->getOperand(1).getNode(), m_block);

        int64_t irCond = node->getImmI64();

        // 使用静态函数映射
        CondCode cc = mapFcmpCond(irCond);
        switch (cc){
            case CondCode::EQ:{
                m_block->insts.push_back(createRInst_impl(Operator::FEQ_S, dst, lhs, rhs, "fcmp eq"));
                break;}
            case CondCode::LT:{
                m_block->insts.push_back(createRInst_impl(Operator::FLT_S, dst, lhs, rhs, "fcmp lt"));
                break;}
            case CondCode::LE:{
                m_block->insts.push_back(createRInst_impl(Operator::FLE_S, dst, lhs, rhs, "fcmp le"));
                break;}
            case CondCode::GT:{
                m_block->insts.push_back(createRInst_impl(Operator::FLT_S, dst, rhs, lhs, "fcmp gt"));
                break;}
            case CondCode::GE:{
                m_block->insts.push_back(createRInst_impl(Operator::FLE_S, dst, rhs, lhs, "fcmp ge"));
                break;}
            case CondCode::NE:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::FEQ_S, tmp, lhs, rhs, "fcmp ne"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, tmp, 1, "fcmp ne"));
                break;}
            case CondCode::ULT:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::FLT_S, tmp, lhs, rhs, "fcmp ult"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, tmp, 1, "fcmp ult"));
                break;}
            case CondCode::ULE:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::FLE_S, tmp, lhs, rhs, "fcmp ule"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, tmp, 1, "fcmp ule"));
                break;}
            case CondCode::UGT:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::FLT_S, tmp, rhs, lhs, "fcmp ugt"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, tmp, 1, "fcmp ugt"));
                break;}
            case CondCode::UGE:{
                Register tmp = getVReg(BE::I64);
                m_block->insts.push_back(createRInst_impl(Operator::FLE_S, tmp, rhs, lhs, "fcmp uge"));
                m_block->insts.push_back(createIInst_impl(Operator::XORI, dst, tmp, 1, "fcmp uge"));
                break;}
            default:
                assert(false && "unsupported fcmp cond");
        }
        
    }

    void DAGIsel::selectBranch(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择分支节点（BR / BRCOND）
        // ============================================================================
        //
        // 作用：
        // 为无条件分支与条件分支生成跳转指令。
        // - BR 直接跳转，用 JAL x0, label
        // - BRCOND 需判断条件（非 0 为真），生成 BNE + JAL 序列

        // TODO("选择分支：区分 BR/BRCOND 生成跳转指令");
        using namespace BE::DAG;
        ISD opc = static_cast<ISD>(node->getOpcode());

        // ================================
        // 无条件跳转：BR
        // ================================
        if (opc == ISD::BR) {
            const SDNode* dest = node->getOperand(1).getNode();
            if (!dest) return;

            RV64::Label lbl(static_cast<int>(dest->getId()), false);
            m_block->insts.push_back(
                createJInst_impl(Operator::JAL, 0, lbl, "uncond branch")
            );
            return;
        }

        // ================================
        // 条件跳转：BRCOND
        // ================================
        if (opc == ISD::BRCOND) {
            const SDNode* condNode  = node->getOperand(1).getNode();
            const SDNode* trueNode  = node->getOperand(2).getNode();
            const SDNode* falseNode = node->getOperand(3).getNode();
            if (!condNode || !trueNode || !falseNode) return;

            Register condReg = getOperandReg(condNode, m_block);

            RV64::Label trueLbl(static_cast<int>(trueNode->getId()), false);
            RV64::Label falseLbl(static_cast<int>(falseNode->getId()), false);

            // if (condReg != 0) goto true
            m_block->insts.push_back(
                createBInst_impl(
                    Operator::BNE,
                    condReg,
                    0,
                    trueLbl,
                    "brcond true"
                )
            );

            // else goto false
            m_block->insts.push_back(
                createJInst_impl(
                    Operator::JAL,
                    0,
                    falseLbl,
                    "brcond false"
                )
            );
            return;
        }
    }

    void DAGIsel::selectCall(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择 CALL 节点
        // ============================================================================
        //
        // 作用：
        // 为函数调用生成参数传递、CALL 指令、返回值处理的完整序列。
        // - 需要遵循目标调用约定（参数寄存器 vs 栈传参）
        // - 整数与浮点参数使用不同的寄存器组
        // - 内置函数（llvm.memset 等）需特殊处理，转化为对 memset 的调用
        //
        // 关键步骤：
        // - 提取函数名（SYMBOL 节点）
        // - 收集参数并分类（整数 vs 浮点）
        // - 前 8 个整数参数 → a0-a7，前 8 个浮点参数 → fa0-fa7
        // - 超出的参数 → 存储到栈上（SP + 0, SP + 8, ...）
        // - 返回值从 a0/fa0 搬运到目标寄存器

        // TODO("选择 CALL：参数传递 + 生成调用指令 + 返回值处理");
        using namespace BE::Targeting::RV64;

        // 1. 获取被调用函数名
        const DAG::SDNode* calleeNode = node->getOperand(1).getNode();
        if (!calleeNode || !calleeNode->hasSymbol()) return;
        const std::string& funcName = calleeNode->getSymbol();

        // 2. 准备参数寄存器列表（a0-a7 / fa0-fa7）
        std::vector<int> intRegs  = {10,11,12,13,14,15,16,17};  // a0-a7
        std::vector<int> floatRegs= {10,11,12,13,14,15,16,17};  // fa0-fa7
        int intRegIdx = 0;
        int floatRegIdx = 0;
        int stackIdx = 0; // 栈溢出参数计数

        // 3. 遍历参数
        for (unsigned i = 2; i < node->getNumOperands(); ++i)
        {
            const DAG::SDNode* argNode = node->getOperand(i).getNode();
            BE::Register srcReg = getOperandReg(argNode, m_block);

            if (srcReg.dt->dt == DataType::Type::FLOAT)
            {
                if (floatRegIdx < (int)floatRegs.size())
                {
                    // 放寄存器 fa0-fa7
                    BE::Register phys = floatRegs[floatRegIdx++];
                    m_block->insts.push_back(
                        new BE::MoveInst(
                            new BE::RegOperand(phys),
                            new BE::RegOperand(srcReg),
                            "call arg float"
                        )
                    );
                }
                else
                {
                    // 栈传参
                    int offset = stackIdx * 8;
                    BE::Register sp = 2; // SP
                    m_block->insts.push_back(
                        createSInst_impl(Operator::SD, srcReg, sp, offset, "call arg float stack")
                    );
                    stackIdx++;
                    floatRegIdx++;
                }
            }
            else
            {
                if (intRegIdx < (int)intRegs.size())
                {
                    // 放寄存器 a0-a7
                    BE::Register phys = intRegs[intRegIdx++];
                    m_block->insts.push_back(
                        new BE::MoveInst(
                            new BE::RegOperand(phys),
                            new BE::RegOperand(srcReg),
                            "call arg int"
                        )
                    );
                }
                else
                {
                    // 栈传参
                    int offset = stackIdx * 8;
                    BE::Register sp = 2; // SP
                    m_block->insts.push_back(
                        createSInst_impl(Operator::SD, srcReg, sp, offset, "call arg int stack")
                    );
                    stackIdx++;
                    intRegIdx++;
                }
            }
        }

        // 4. 生成 CALL 占位指令
        m_block->insts.push_back(
            createCallInst_impl(
                Operator::CALL,
                funcName,
                intRegIdx,   // 已用整数寄存器数量
                floatRegIdx, // 已用浮点寄存器数量
                "call " + funcName
            )
        );

        // 5. 处理返回值
        if (node->getNumValues() > 0)
        {
            BE::Register dst = nodeToVReg_.at(node);
            BE::Register retPhys;
            if (dst.dt->dt == DataType::Type::FLOAT)
                retPhys = 10;  // fa0
            else
                retPhys = 10;  // a0

            m_block->insts.push_back(
                new BE::MoveInst(
                    new BE::RegOperand(dst),  // 目标虚拟寄存器
                    new BE::RegOperand(retPhys),
                    "call ret"
                )
            );
        }
    }


    void DAGIsel::selectRet(const DAG::SDNode* node, BE::Block* m_block)
    {
        // 操作数 0 是 Chain（保证副作用顺序），操作数 1 是实际返回值
        // 如有返回值，则将返回值移动到 a0 / fa0
        if (node->getNumOperands() > 1)
        {
            const DAG::SDNode* retValNode = node->getOperand(1).getNode();

            Register retReg = getOperandReg(retValNode, m_block);

            DataType* retType = retValNode->getNumValues() > 0 ? retValNode->getValueType(0) : BE::I32;
            Register  destReg = (retType == BE::F32 || retType == BE::F64) ? PR::fa0 : PR::a0;

            m_block->insts.push_back(createMove(new RegOperand(destReg), new RegOperand(retReg), LOC_STR));
        }

        m_block->insts.push_back(createIInst(Operator::JALR, PR::x0, PR::ra, 0));
    }

    void DAGIsel::selectCast(const DAG::SDNode* node, BE::Block* m_block)
    {
        // ============================================================================
        // TODO: 选择类型转换节点（ZEXT / SITOFP / FPTOSI）
        // ============================================================================
        //
        // 作用：
        // 为类型转换节点生成目标相关的转换指令。

        // TODO("选择类型转换：生成 FCVT 或扩展指令");
        using namespace BE::DAG;
        auto opcode = static_cast<ISD>(node->getOpcode());
        Register dst = nodeToVReg_.at(node);
        Register src = getOperandReg(node->getOperand(0).getNode(), m_block);
        switch(opcode) {
            case ISD::ZEXT: {
                const DAG::SDNode* srcNode = node->getOperand(0).getNode();
                auto srcOpcode = static_cast<ISD>(srcNode->getOpcode());

                if (srcOpcode == ISD::ICMP || srcOpcode == ISD::FCMP) {
                    // 比较结果：只保留 bit0
                    m_block->insts.push_back(
                        createRInst(Operator::ZEXT_W, dst, src, 0)
                    );
                }
                break;
            }
            case ISD::SITOFP: {
                // 整数转浮点
                m_block->insts.push_back(
                    createRInst(Operator::FCVT_S_W, dst, src, 0)
                );
                break;
            }
            case ISD::FPTOSI: {
                // 浮点转整数
                m_block->insts.push_back(
                    createRInst(Operator::FCVT_W_S, dst, src, 0)
                );
                break;
            }
            default:
                ERROR("Unsupported cast operator: %d", node->getOpcode());
        }
    }

    void DAGIsel::selectNode(const DAG::SDNode* node, BE::Block* m_block)
    {
        if (!node) return;

        auto opcode = static_cast<DAG::ISD>(node->getOpcode());

        switch (opcode)
        {
            case DAG::ISD::FRAME_INDEX:
            case DAG::ISD::CONST_I32:
            case DAG::ISD::CONST_I64:
            case DAG::ISD::CONST_F32:
            case DAG::ISD::REG:
            case DAG::ISD::LABEL:
            case DAG::ISD::SYMBOL:
            case DAG::ISD::ENTRY_TOKEN:
            case DAG::ISD::TOKEN_FACTOR: break;
            case DAG::ISD::COPY: selectCopy(node, m_block); break;
            case DAG::ISD::PHI: selectPhi(node, m_block); break;
            case DAG::ISD::ADD:
            case DAG::ISD::SUB:
            case DAG::ISD::MUL:
            case DAG::ISD::DIV:
            case DAG::ISD::MOD:
            case DAG::ISD::AND:
            case DAG::ISD::OR:
            case DAG::ISD::XOR:
            case DAG::ISD::SHL:
            case DAG::ISD::ASHR:
            case DAG::ISD::LSHR:
            case DAG::ISD::FADD:
            case DAG::ISD::FSUB:
            case DAG::ISD::FMUL:
            case DAG::ISD::FDIV: selectBinary(node, m_block); break;
            case DAG::ISD::LOAD: selectLoad(node, m_block); break;
            case DAG::ISD::STORE: selectStore(node, m_block); break;
            case DAG::ISD::ICMP: selectICmp(node, m_block); break;
            case DAG::ISD::FCMP: selectFCmp(node, m_block); break;
            case DAG::ISD::BR:
            case DAG::ISD::BRCOND: selectBranch(node, m_block); break;
            case DAG::ISD::CALL: selectCall(node, m_block); break;
            case DAG::ISD::RET: selectRet(node, m_block); break;
            case DAG::ISD::ZEXT:
            case DAG::ISD::SITOFP:
            case DAG::ISD::FPTOSI: selectCast(node, m_block); break;

            default: ERROR("Unsupported DAG node: %s", DAG::toString(static_cast<DAG::ISD>(node->getOpcode())));
        }
    }

    void DAGIsel::selectBlock(ME::Block* ir_block, const DAG::SelectionDAG& dag)
    {
        // ============================================================================
        // TODO: 选择基本块的所有指令
        // ============================================================================
        //
        // 作用：
        // 将一个基本块的 DAG 转换为 MIR 指令序列。
        //
        // 采用两阶段：
        // - 阶段 1：调度与寄存器分配
        //   * 调度 DAG 节点，确定指令顺序
        //   * 为每个节点预分配虚拟寄存器（如果不预分配会怎么样？可以怎么解决？）
        // - 阶段 2：指令选择
        //   * 按调度顺序遍历节点，调用 selectNode 生成具体指令
        //   * 使用已选择集合避免重复选择

        // TODO("选择基本块：调度 + 分配寄存器 + 生成指令");
        nodeToVReg_.clear();
        selected_.clear();

        auto it = ctx_.mfunc->blocks.find(ir_block->blockId);
        ASSERT(it != ctx_.mfunc->blocks.end() && "Missing backend block");

        BE::Block* m_block = it->second;
        std::vector<const DAG::SDNode*> schedule = scheduleDAG(dag);
        for (const DAG::SDNode* node : schedule)
        {
            allocateRegistersForNode(node);
        }
        for (const DAG::SDNode* node : schedule)
        {
            if (selected_.count(node)) continue;
            selectNode(node, m_block);
        }
    }

    void DAGIsel::selectFunction(ME::Function* ir_func)
    {
        // ============================================================================
        // TODO: 选择函数的所有指令
        // ============================================================================
        //
        // 作用：
        // 协调整个函数的指令选择流程，包括栈帧管理、参数设置、基本块选择。
        //
        // 为什么需要函数级初始化：
        // - 每个函数有独立的虚拟寄存器空间（vregMap、nodeToVReg_）
        // - 需要计算栈帧布局（传出参数区、局部变量区）
        // - 需要创建所有基本块的 MIR 对象
        //
        // 关键步骤：
        // 1. 重置上下文
        ctx_ = FunctionContext{};
        nodeToVReg_.clear();
        selected_.clear();
        // 2. 创建后端函数对象
        auto* mfunc = new BE::Function(ir_func->funcDef->funcName);
        m_backend_module->functions.push_back(mfunc);
        ctx_.mfunc = mfunc;
        // 3. 计算传出参数区大小
        collectCall(ir_func);
        // 4. 收集局部变量
        collectAllocas(ir_func);
        // 5. 创建所有基本块对象
        for (auto& [label, ir_block] : ir_func->blocks)
        {
            auto* mblock = new BE::Block(label);
            ctx_.mfunc->blocks.emplace(label, mblock);

        }
        // 6. 为参数分配虚拟寄存器
        setupParameters(ir_func);
        // 7. 对每个基本块做指令选择
        for (auto& [label, ir_block] : ir_func->blocks)
        {
            DAG::SelectionDAG dag;
            DAG::DAGBuilder builder;
            builder.visit(*ir_block, dag);
            selectBlock(ir_block, dag);
        }
        // TODO("选择函数：初始化上下文 + 栈帧管理 + 逐块选择");

    }

    void DAGIsel::runImpl()
    {
        importGlobals();

        target_->buildDAG(ir_module_);

        for (auto* f : ir_module_->functions) selectFunction(f);
    }

}  // namespace BE::RV64
