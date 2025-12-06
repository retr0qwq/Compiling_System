#include <middleend/visitor/codegen/ast_codegen.h>

namespace ME
{
    void ASTCodeGen::visit(FE::AST::LeftValExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成左值表达式的取址/取值 IR
        // 查找变量位置（全局或局部），处理数组下标/GEP，必要时发出load
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement LeftValExpr IR generation");
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
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement UnaryExpr IR generation");
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
                    ERROR("Unsupported type for NEG operator");
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
    }

    void ASTCodeGen::handleAssign(FE::AST::LeftValExpr& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成赋值语句的 IR（计算右值、类型转换、store 到左值地址）
        (void)lhs;
        (void)rhs;
        (void)m;
        TODO("Lab3-2: Implement assignment IR generation");
    }
    void ASTCodeGen::handleLogicalAnd(
        FE::AST::BinaryExpr& node, FE::AST::ExprNode& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成短路与的基本块与条件分支
        (void)node;
        (void)lhs;
        (void)rhs;
        (void)m;
        TODO("Lab3-2: Implement logical AND codegen");
    }
    void ASTCodeGen::handleLogicalOr(
        FE::AST::BinaryExpr& node, FE::AST::ExprNode& lhs, FE::AST::ExprNode& rhs, Module* m)
    {
        // TODO(Lab 3-2): 生成短路或的基本块与条件分支
        (void)node;
        (void)lhs;
        (void)rhs;
        (void)m;
        TODO("Lab3-2: Implement logical OR codegen");
    }
    void ASTCodeGen::visit(FE::AST::BinaryExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成二元表达式 IR（含赋值、逻辑与/或、算术/比较）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement BinaryExpr IR generation");
    }

    void ASTCodeGen::visit(FE::AST::CallExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 生成函数调用 IR（准备参数、可选返回寄存器、发出call）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement CallExpr IR generation");
    }

    void ASTCodeGen::visit(FE::AST::CommaExpr& node, Module* m)
    {
        // TODO(Lab 3-2): 依序生成逗号表达式每个子表达式的 IR
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement CommaExpr IR generation");
    }
}  // namespace ME
