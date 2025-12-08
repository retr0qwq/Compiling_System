#include <middleend/visitor/codegen/ast_codegen.h>
#include <middleend/module/ir_instruction.h>
using namespace FE::AST;
namespace ME
{
    void ASTCodeGen::visit(FE::AST::LeftValExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成左值表达式的取址/取值 IR
        // 查找变量位置（全局或局部），处理数组下标/GEP，必要时发出load
        // TODO("Lab3-2: Implement LeftValExpr IR generation");
        FE::AST::VarAttr* attr = nullptr;
        size_t varReg = static_cast<size_t>(-1);
        Operand* ptrOp = nullptr;
        // 若为全局变量
        if (glbSymbols.find(node.entry) != glbSymbols.end())
        {
            attr   = const_cast<FE::AST::VarAttr*>(&(glbSymbols.at(node.entry)));
            ptrOp = getGlobalOperand(node.entry->getName());
        }
        else if (name2reg.getReg(node.entry) != static_cast<size_t>(-1)) // 局部变量
        {
            attr   = &(reg2attr[name2reg.getReg(node.entry)]);
            varReg = name2reg.getReg(node.entry);
            lval2ptr[&node] = getRegOperand(varReg);
            ptrOp = lval2ptr[&node];
        }
        else
        {
            ERROR("Variable not found in symbol tables");
        }
        /*
        if (!node.indices || node.indices->empty())
        {
            // 标量变量，直接取地址
            lval2ptr[&node] = getRegOperand(varReg);
        }
        else
        {
             数组变量，计算偏移后取地址
            std::vector<size_t> indexRegs;
            // 计算每个下标表达式
            for (auto* indexExpr : *(node.indices))
            {
                apply(*this, *indexExpr, m);
                indexRegs.push_back(getMaxReg());
            }
            size_t ptrReg = getNewRegId();
            auto gepInst  = createGEPInst(convert(attr->type), varReg, indexRegs, ptrReg);
            insert(gepInst);
            lval2ptr[&node] = createOperandPtr(ptrReg);
            
        }
         */ 
        if (!node.isLval){
            size_t resReg = getNewRegId();
            auto loadInst = createLoadInst(convert(attr->type), ptrOp, resReg);
            insert(loadInst);
        }
    }

    void ASTCodeGen::visit(FE::AST::LiteralExpr& node, Module* m)
    {
        (void)m;

        size_t reg = getNewRegId();
        switch (node.literal.type->getBaseType())
        {
            case FE::AST::Type_t::INT:
            case FE::AST::Type_t::LL:  // treat as I32
            {
                int             val  = node.literal.getInt();
                ArithmeticInst* inst = createArithmeticI32Inst_ImmeAll(Operator::ADD, val, 0, reg);  // reg = val + 0
                insert(inst);
                break;
            }
            case FE::AST::Type_t::FLOAT:
            {
                float           val  = node.literal.getFloat();
                ArithmeticInst* inst = createArithmeticF32Inst_ImmeAll(Operator::FADD, val, 0, reg);  // reg = val + 0
                insert(inst);
                break;
            }
            default: ERROR("Unsupported literal type");
        }
    }

    void ASTCodeGen::visit(FE::AST::UnaryExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成一元运算的 IR（访问操作数、必要的类型转换、发出运算指令）
        // TODO("Lab3-2: Implement UnaryExpr IR generation");
        /*
        apply(*this, node.expr, m);
        size_t operandReg = getMaxReg();
        auto op = node.op;
        FE::AST::Type* tp = node.expr->attr.val.value.type;
        DataType dt = convert(tp);
        size_t dstReg = getNewRegId();
        // 根据操作符判断
        switch (op)
        {
            case FE::AST::Operator::SUB:
            {
                if (dt == DataType::I32)
                {
                    insert(createArithmeticI32Inst_ImmeLeft(Operator::SUB, 0, operandReg, dstReg));
                }
                else if (dt == DataType::F32)
                {
                    insert(createArithmeticF32Inst_ImmeLeft(Operator::FSUB, 0.0f, operandReg, dstReg));
                }
                else if (dt == DataType::I1)
                {
                    auto convInsts = createTypeConvertInst(DataType::I1, DataType::I32, operandReg);
                    for (auto* inst : convInsts)
                        insert(inst);
                    operandReg = getMaxReg();
                    insert(createArithmeticI32Inst_ImmeLeft(Operator::SUB, 0, operandReg, dstReg));
                }
                else
                {
                    ERROR("Unsupported type for SUB operator");
                }
                break;
            }
            case FE::AST::Operator::NOT:
            {
                if (dt == DataType::I1)
                {
                    insert(createIcmpInst_ImmeRight(ICmpOp::EQ, operandReg, 0, dstReg));
                }
                else if (dt == DataType::I32)
                {
                    insert(createIcmpInst_ImmeRight(ICmpOp::EQ, operandReg, 0, dstReg));
                }
                else if (dt == DataType::F32)
                {
                    // 比较是否等于0.0f
                    insert(createFcmpInst_ImmeRight(FCmpOp::OEQ, operandReg, 0.0f, dstReg));
                }
                else
                {
                    ERROR("Unsupported type for NOT operator");
                }
                break;
            }
            case FE::AST::Operator::ADD:
                // 正号，直接传递操作数
                {
                    if (dt == DataType::I32)
                    {
                        insert(createArithmeticI32Inst_ImmeLeft(Operator::ADD, 0, operandReg, dstReg));
                    }
                    else if (dt == DataType::F32)
                    {
                        insert(createArithmeticF32Inst_ImmeLeft(Operator::FADD, 0.0f, operandReg, dstReg));
                    }
                    else if (dt == DataType::I1)
                    {
                    auto convInsts = createTypeConvertInst(DataType::I1, DataType::I32, operandReg);
                    for (auto* inst : convInsts)
                        insert(inst);
                    operandReg = getMaxReg(); 
                    insert(createArithmeticI32Inst_ImmeLeft(Operator::ADD, 0, operandReg, dstReg));
                    }
                    else
                    {
                        ERROR("Unsupported type for POS operator");
                    }
                }
                break;
            default:
                ERROR("Unsupported unary operator");
        }
        */
        handleUnaryCalc(*node.expr, node.op, curBlock, m);
    }

    void ASTCodeGen::handleAssign(FE::AST::LeftValExpr& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成赋值语句的 IR（计算右值、类型转换、store 到左值地址）
        // TODO("Lab3-2: Implement assignment IR generation");
        lhs.isLval = true;
        apply(*this, lhs, m);
        DataType lhsType = convert( lhs.attr.val.value.type);
        apply(*this, rhs, m);
        size_t rhsReg= getMaxReg();
        DataType rhsType = convert( rhs.attr.val.value.type);
        if (lhsType != rhsType) {
            auto convInsts = createTypeConvertInst(rhsType, lhsType, rhsReg);
            for (auto* inst : convInsts)
                insert(inst);
            rhsReg = getMaxReg();
        }
        Operand* lshPtr = lval2ptr[&lhs];
        insert( createStoreInst(lhsType, rhsReg, lshPtr));
        lhs.isLval = false;
    }
    void ASTCodeGen::handleLogicalAnd(
        FE::AST::BinaryExpr& node, FE::AST::ExprNode& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成短路与的基本块与条件分支
        // TODO("Lab3-2: Implement logical AND codegen");
        size_t parenttrue = node.trueTar;
        size_t parentfalse = node.falseTar;
        Block* rhsBlock = createBlock();
        lhs.trueTar = rhsBlock->blockId;
        lhs.falseTar = parentfalse;
        rhs.trueTar = parenttrue;
        rhs.falseTar = parentfalse;
        apply(*this, lhs, m);
        size_t lhsReg = getMaxReg();
        DataType lhsType = convert(lhs.attr.val.value.type);
        ASSERT(lhsType == DataType::I1 || lhsType == DataType::I32);  // 布尔/整型

        // 如果 lhs 不是 i1，需要转换
        if (lhsType != DataType::I1) {
            auto convInsts = createTypeConvertInst(lhsType, DataType::I1, lhsReg);
            for (auto* inst : convInsts)
                insert(inst);
            lhsReg = getMaxReg();
        }
        insert(createBranchInst(lhsReg, lhs.trueTar, lhs.falseTar));
        // 进入 rhsBlock
        curFunc->blocks[rhsBlock->blockId] = rhsBlock;
        enterBlock(rhsBlock);
        apply(*this, rhs, m);
        size_t rhsReg = getMaxReg();
        DataType rhsType = convert(rhs.attr.val.value.type);
        if (rhsType != DataType::I1) {
            auto convInsts = createTypeConvertInst(rhsType, DataType::I1, rhsReg);
            for (auto* inst : convInsts)
                insert(inst);
            rhsReg = getMaxReg();
        }
        insert(createBranchInst(rhsReg, rhs.trueTar, rhs.falseTar));
    }
    void ASTCodeGen::handleLogicalOr(
        FE::AST::BinaryExpr& node, FE::AST::ExprNode& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成短路或的基本块与条件分支
        //TODO("Lab3-2: Implement logical OR codegen");
        size_t parenttrue = node.trueTar;
        size_t parentfalse = node.falseTar;
        Block* rhsBlock = createBlock();
        lhs.trueTar = parenttrue;
        lhs.falseTar = rhsBlock->blockId; 
        rhs.trueTar = parenttrue;
        rhs.falseTar = parentfalse;
        apply(*this, lhs, m);
        size_t lhsReg = getMaxReg();
        DataType lhsType = convert(lhs.attr.val.value.type);
        ASSERT(lhsType == DataType::I1 || lhsType == DataType::I32);  // 布尔/整型

        // 如果 lhs 不是 i1，需要转换
        if (lhsType != DataType::I1) {
            auto convInsts = createTypeConvertInst(lhsType, DataType::I1, lhsReg);
            for (auto* inst : convInsts)
                insert(inst);
            lhsReg = getMaxReg();
        }
        insert(createBranchInst(lhsReg, lhs.trueTar, lhs.falseTar));
        // 进入 rhsBlock
        curFunc->blocks[rhsBlock->blockId] = rhsBlock;
        enterBlock(rhsBlock);
        apply(*this, rhs, m);
        size_t rhsReg = getMaxReg();
        DataType rhsType = convert(rhs.attr.val.value.type);
        if (rhsType != DataType::I1) {
            auto convInsts = createTypeConvertInst(rhsType, DataType::I1, rhsReg);
            for (auto* inst : convInsts)
                insert(inst);
            rhsReg = getMaxReg();
        }
        insert(createBranchInst(rhsReg, rhs.trueTar, rhs.falseTar));
    }
    void ASTCodeGen::visit(FE::AST::BinaryExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成二元表达式 IR（含赋值、逻辑与/或、算术/比较）
        // TODO("Lab3-2: Implement BinaryExpr IR generation");
        auto op = node.op;
        if (op == FE::AST::Operator::AND)
        {
            handleLogicalAnd(node, *node.lhs, *node.rhs, m);
        }
        else if (op == FE::AST::Operator::OR)
        {
            handleLogicalOr(node, *node.lhs, *node.rhs, m);
        }
        else if (op == FE::AST::Operator::ASSIGN)
        {
            // 赋值表达式特殊处理
            LeftValExpr* lval = dynamic_cast<LeftValExpr*>(node.lhs);
            if (!lval)
            {
                ERROR("Left-hand side of assignment must be a left value");
            }
            handleAssign(*lval, *node.rhs, m);
        }
        else
        {
            handleBinaryCalc(*node.lhs, *node.rhs, op, curBlock, m);
        }
    }

    void ASTCodeGen::visit(FE::AST::CallExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成函数调用 IR（准备参数、可选返回寄存器、发出call）
        // TODO("Lab3-2: Implement CallExpr IR generation");
        auto* funcDecl = funcDecls.at(node.func);
        CallInst::argList args;

        // 如果函数有参数且 node.args 非空
        if (node.args && !node.args->empty()) {
            for (size_t i = 0; i < node.args->size(); i++) {
                auto* argExpr = node.args->at(i);
                apply(*this, *argExpr, m);                  // 生成参数 IR
                size_t argReg = getMaxReg();                // 获取参数寄存器
                DataType argType = convert(argExpr->attr.val.value.type);
                Type* paramType = funcDecl->params->at(i)->type;
                DataType paramDT = convert(paramType);

                // 参数类型转换
                if (argType != paramDT) {
                    auto convInsts = createTypeConvertInst(argType, paramDT, argReg);
                    for (auto* inst : convInsts) insert(inst);
                    argReg = getMaxReg();
                }

                args.push_back(CallInst::argPair(paramDT, getRegOperand(argReg)));
            }
        }
        DataType retType = convert(funcDecl->retType);
        if (!args.empty() && retType != DataType::VOID) {
            size_t retReg = getNewRegId();
            insert(createCallInst(retType, node.func->getName(), args, retReg));
            reg2attr[retReg] = VarAttr{funcDecl->retType};
        } 
        else if (!args.empty() && retType == DataType::VOID) {
            insert(createCallInst(retType, node.func->getName(), args));
        } 
        else if (args.empty() && retType != DataType::VOID) {
            size_t retReg = getNewRegId();
            insert(createCallInst(retType, node.func->getName(), retReg));
            reg2attr[retReg] = VarAttr{funcDecl->retType};
        } 
        else { // args.empty() && retType == VOID
            insert(createCallInst(retType, node.func->getName()));
        }
    }

    void ASTCodeGen::visit(FE::AST::CommaExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 依序生成逗号表达式每个子表达式的 IR
        // TODO("Lab3-2: Implement CommaExpr IR generation");
        ASSERT(node.exprs && "Comma expression list is null");
        for (auto* expr : *(node.exprs))
        {
            apply(*this, *expr, m);
        }
    }
}  // namespace ME
