#include <frontend/ast/visitor/sementic_check/ast_checker.h>
#include <debug.h>

namespace FE::AST
{
    bool ASTChecker::visit(LeftValExpr& node)
    {
        // TODO(Lab3-1): 实现左值表达式的语义检查
        // 检查变量是否存在，处理数组下标访问，进行类型检查和常量折叠
        //TODO("Lab3-1: Implement LeftValExpr semantic checking");
        VarAttr* attr = symTable.getSymbol_impl(node.entry);
        if (!attr) {
            errors.emplace_back("Error: Undefined variable '" + node.entry->getName() + "'.");
            return false;
        }

        size_t dimCount = node.indices ? node.indices->size() : 0;
        size_t totalDims = attr->arrayDims.size();

        if (dimCount > totalDims) {
            errors.emplace_back("Error: Too many indices for variable '" + node.entry->getName() + "'.");
            return false;
        }

        bool allConst = true;
        node.isLval = true;
        std::vector<int> idxValues;
        size_t dimleft = totalDims - dimCount;
        TypeFactory& tf = TypeFactory::getInstance();
        // 遍历每个下标表达式
        for (size_t i = 0; i < dimCount; ++i) {
            ExprNode* idxNode = (*(node.indices))[i];
            if (!apply(*this, *idxNode)) return false;

            Type_t idxType = idxNode->attr.val.value.type->getBaseType();
            if (idxType != Type_t::INT && idxType != Type_t::LL && idxType != Type_t::BOOL) {
                errors.emplace_back("Error: Array index must be of integer type.");
                return false;
            }

            // 保存下标常量值
            if (idxNode->attr.val.isConstexpr) {
                int val = 0;
                if (idxType == Type_t::INT) val = idxNode->attr.val.getInt();
                else if (idxType == Type_t::LL) val = static_cast<int>(idxNode->attr.val.getLL());
                else if (idxType == Type_t::BOOL) val = idxNode->attr.val.getBool() ? 1 : 0;
                idxValues.push_back(val);
            } else {
                allConst = false;
                idxValues.push_back(0); // 占位
            }
        }

        if (dimleft == 0) {
            // 完全索引，结果为标量
            node.attr.val.value.type = attr->type;
            node.attr.val.isConstexpr = (attr->isConstDecl && allConst);
            // 常量折叠
            if (node.attr.val.isConstexpr && !attr->initList.empty()) {
                // 计算线性偏移 pos
                int pos = 0;
                for (size_t i = 0; i < dimCount; ++i) {
                    int idx = idxValues[i];
                    // 越界检查
                    if (idx < 0 || idx >= static_cast<int>(attr->arrayDims[i])) {
                        errors.emplace_back("Error: Array index out of bounds for variable '" +
                                            node.entry->getName() + "'.");
                        node.attr.val.isConstexpr = false;
                        return false;
                    }
                    pos = pos * attr->arrayDims[i] + idx;
                }
                if (pos < static_cast<int>(attr->initList.size())) {
                    node.attr.val = ExprValue(attr->initList[pos], true);
                } else {
                    errors.emplace_back("Error: Internal array initList size mismatch.");
                    node.attr.val.isConstexpr = false;
                }
            }
        } else {

            Type* baseType = attr->type;
            for (size_t i = 0; i < dimleft; ++i) {
                Type* t = attr->type;
                for (size_t i = 0; i < dimleft; ++i) {
                    t = tf.getPtrType(t);
                }
                node.attr.val.value.type = t;
                node.attr.val.isConstexpr = false;
            }
            node.attr.val.value.type = baseType;
        }

        
        return true;
    }

    bool ASTChecker::visit(LiteralExpr& node)
    {
        // 示例实现：字面量表达式的语义检查
        // 字面量总是编译期常量，直接设置属性
        node.attr.val.isConstexpr = true;
        node.attr.val.value       = node.literal;
        return true;
    }

    bool ASTChecker::visit(UnaryExpr& node)
    {
        // TODO(Lab3-1): 实现一元表达式的语义检查
        // 访问子表达式，检查操作数类型，调用类型推断函数
        //TODO("Lab3-1: Implement UnaryExpr semantic checking");
        bool res = apply(*this, *(node.expr));
        if(!res) return false;
        Type* expr_type = node.expr->attr.val.value.type;
        if(node.op == Operator::NOT) {
            if(expr_type->getBaseType() != Type_t::BOOL) {
                errors.emplace_back("Error: Invalid operand type for '!' operator.");
                return false;
            }
        }
        if (node.op != Operator::SUB && node.op != Operator::NOT) {
        errors.emplace_back("Error: Unsupported unary operator.");
        return false;
        }
        bool hasError = false;
        ExprValue result = typeInfer(node.expr->attr.val, node.op, node, hasError);
        if (hasError) return false;
        node.attr.val.value.type = result.value.type;
        node.attr.val.isConstexpr = result.isConstexpr;
        node.attr.val = result;

        return true;
    }

    bool ASTChecker::visit(BinaryExpr& node)
    {
        // TODO(Lab3-1): 实现二元表达式的语义检查
        // 访问左右子表达式，检查操作数类型，调用类型推断
        //TODO("Lab3-1: Implement BinaryExpr semantic checking");
        if (!apply(*this, *node.lhs)) return false;
        if (!apply(*this, *node.rhs)) return false;

        Type* lhsType = node.lhs->attr.val.value.type;
        Type* rhsType = node.rhs->attr.val.value.type;
        Type_t lhsBase = lhsType->getBaseType();
        Type_t rhsBase = rhsType->getBaseType();

        //检查运算符类型合法性
        switch (node.op) {
            case Operator::ADD:
            case Operator::SUB:
            case Operator::MUL:
            case Operator::DIV:
            case Operator::MOD:
                // 数值运算要求操作数为 INT/LL/FLOAT
                if ((lhsBase == Type_t::BOOL) && (rhsBase == Type_t::BOOL)) {
                    // bool + bool → promote -> int（SysY 允许）
                    break;
                }
                if (lhsBase == Type_t::BOOL || rhsBase == Type_t::BOOL) {
                    errors.emplace_back("Error: arithmetic operator cannot apply to boolean type.");
                    return false;
                }
                if (node.op == Operator::MOD &&
                    (lhsBase == Type_t::FLOAT || rhsBase == Type_t::FLOAT)) {
                    errors.emplace_back("Error: '%' operator cannot be applied to float type.");
                    return false;
                }
                break;

            case Operator::BITAND:
            case Operator::BITOR:
                // 位运算仅允许整型
                if (lhsBase == Type_t::FLOAT || rhsBase == Type_t::FLOAT) {
                    errors.emplace_back("Error: bitwise operator cannot apply to float type.");
                    return false;
                }
                break;

            case Operator::AND:
            case Operator::OR:
                // 逻辑运算要求布尔类型
                if (lhsBase != Type_t::BOOL || rhsBase != Type_t::BOOL) {
                    errors.emplace_back("Error: logical operator requires boolean operands.");
                    return false;
                }
                break;

            case Operator::GT: case Operator::GE:
            case Operator::LT: case Operator::LE:
            case Operator::EQ: case Operator::NEQ:
                break;
            case Operator::ASSIGN:
                if (dynamic_cast<LeftValExpr*>(node.lhs) == nullptr||!dynamic_cast<LeftValExpr*>(node.lhs)->isLval) {
                    errors.emplace_back("Error: Left-hand side of assignment must be a left value.");
                    return false;
                }
                VarAttr* lhsAttr = symTable.getSymbol_impl(dynamic_cast<LeftValExpr*>(node.lhs)->entry);
                if(!lhsAttr) {
                    errors.emplace_back("Error: Undefined variable '" + dynamic_cast<LeftValExpr*>(node.lhs)->entry->getName() + "'.");
                    return false;
                }
                if (lhsAttr->isConstDecl) {
                    errors.emplace_back("Error: Cannot assign to constant variable '" + dynamic_cast<LeftValExpr*>(node.lhs)->entry->getName() + "'.");
                    return false;
                }
                if (lhsType->getTypeGroup() == TypeGroup::POINTER || rhsType->getTypeGroup() == TypeGroup::POINTER){
                    if(lhsType!=rhsType){
                        errors.emplace_back("Error: Type mismatch in assignment.");
                        return false;
                    }
                }
                else{
                    if (!((lhsBase == Type_t::BOOL || lhsBase == Type_t::INT ||lhsBase == Type_t::LL || lhsBase == Type_t::FLOAT) &&
                            (rhsBase == Type_t::BOOL || rhsBase == Type_t::INT ||rhsBase == Type_t::LL || rhsBase == Type_t::FLOAT)
                        )) {
                        errors.emplace_back("Error: Type mismatch in assignment.");
                        return false;
                    }
                }
                break;
            default:
                errors.emplace_back("Error: Unknown binary operator.");
                return false;
        }

        // 类型推断与常量折叠
        bool hasError = false;
        ExprValue result = typeInfer(node.lhs->attr.val, node.rhs->attr.val,
                                    node.op, node, hasError);
        if (hasError) return false;
        node.attr.val.value.type    = result.value.type;
        node.attr.val.isConstexpr = result.isConstexpr;
        node.attr.val     = result;

        return true;
    }


    bool ASTChecker::visit(CallExpr& node)
    {
        // TODO(Lab3-1): 实现函数调用表达式的语义检查
        // 检查函数是否存在，访问实参列表，检查参数数量和类型匹配
        //TODO("Lab3-1: Implement CallExpr semantic checking");
        if (!node.func) {
            errors.emplace_back("Error: function not defined.");
            return false;
        }
    }

    bool ASTChecker::visit(CommaExpr& node)
    {
        // TODO(Lab3-1): 实现逗号表达式的语义检查
        // 依序访问各子表达式，结果为最后一个表达式的属性
        //TODO("Lab3-1: Implement CommaExpr semantic checking");
        bool res = true;

        // 依序访问子表达式
        for (auto &expr : *(node.exprs)) {
            res &= apply(*this, *expr);
        }
        if (node.exprs->empty()) {
            errors.emplace_back("Error: Comma expression has no sub-expressions.");
            return false;
        }

        // 结果属性取最后一个元素
        auto &lastExpr = *(node.exprs->back());
        node.attr.val.value.type = lastExpr.attr.val.value.type;
        node.attr.val.isConstexpr = lastExpr.attr.val.isConstexpr;
        node.attr.val = lastExpr.attr.val;

        return res;
    }
}  // namespace FE::AST
