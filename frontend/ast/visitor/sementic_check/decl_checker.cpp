#include <frontend/ast/visitor/sementic_check/ast_checker.h>
#include <debug.h>

namespace FE::AST
{
    bool ASTChecker::visit(Initializer& node)
    {
        // 示例实现：单个初始化器的语义检查
        // 1) 访问初始化值表达式
        // 2) 将子表达式的属性拷贝到当前节点
        ASSERT(node.init_val && "Null initializer value");
        bool res  = apply(*this, *node.init_val);
        node.attr = node.init_val->attr;
        return res;
    }

    bool ASTChecker::visit(InitializerList& node)
    {
        // 示例实现：初始化器列表的语义检查
        // 遍历列表中的每个初始化器并逐个访问
        if (!node.init_list) return true;
        bool res = true;
        for (auto* init : *(node.init_list))
        {
            if (!init) continue;
            res &= apply(*this, *init);
        }
        return res;
    }

    bool ASTChecker::visit(VarDeclarator& node)
    {
        // TODO(Lab3-1): 实现变量声明器的语义检查
        // 访问左值表达式，同步属性，处理初始化器（如果有）
        bool res = true;
        auto* lval = dynamic_cast<LeftValExpr*>(node.lval);

        if (!lval) {
            errors.emplace_back("Error: Invalid declarator at line " + std::to_string(node.line_num));
            return false;
        }
        Entry* entry = lval->entry;
        if (symTable.getlocalSymbol_impl(entry)) {
        errors.emplace_back( "Error: Redefinition of variable '" + entry->getName() + "' at line " + std::to_string(node.line_num));
        return false;
        }
        Type* varType = node.attr.val.value.type;
        bool isConst = node.attr.val.isConstexpr;
        auto* varAttr = new VarAttr(varType, isConst, symTable.getScopeDepth_impl());
        symTable.addSymbol_impl(entry, varAttr); 
        if (!apply(*this, *node.lval)) {return false;}
        node.attr.val=node.lval->attr.val;
        if (node.init) {
            res &= apply(*this, *node.init);
            // 类型检查          
            Type* lhsType = varType;
            Type* rhsType = node.init->attr.val.value.type;

            Type_t lhsBase = lhsType->getBaseType();
            Type_t rhsBase = rhsType->getBaseType();
            if (lhsType->getTypeGroup() == TypeGroup::POINTER ||rhsType->getTypeGroup() == TypeGroup::POINTER) {
                if (lhsBase != rhsBase) {
                    errors.emplace_back(
                        "Error: Type mismatch in initialization of '" +lval->entry->getName() + "' at line " +std::to_string(node.line_num)
                    );
                    res = false;
                }
            }
            else {
                bool lhsIsNum = (lhsBase == Type_t::BOOL || lhsBase == Type_t::INT ||lhsBase == Type_t::LL   || lhsBase == Type_t::FLOAT);
                bool rhsIsNum = (rhsBase == Type_t::BOOL || rhsBase == Type_t::INT || rhsBase == Type_t::LL   || rhsBase == Type_t::FLOAT);

                if (!(lhsIsNum && rhsIsNum)) {
                    errors.emplace_back("Error: Type mismatch in initialization of '" +lval->entry->getName() + "' at line " + std::to_string(node.line_num));
                    res = false;
                }
            }

            // 常量变量初始化要求常量表达式
            if (isConst && !node.init->attr.val.isConstexpr) {
                errors.emplace_back("Error: Const variable '" + lval->entry->getName() +"' must be initialized with a constant expression." + std::string("at line ") + std::to_string(node.line_num)             );
                res = false;
            }
        }
        return res;
    }


    bool ASTChecker::visit(ParamDeclarator& node)
    {
        // TODO(Lab3-1): 实现函数形参的语义检查
        // 检查形参重定义，处理数组形参的类型退化，将形参加入符号表
        //TODO("Lab3-1: Implement ParamDeclarator semantic checking");
        if (symTable.getlocalSymbol_impl(node.entry)) {
            errors.emplace_back("Error: Redefinition of parameter '" + node.entry->getName() + "'." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        TypeFactory& tf = TypeFactory::getInstance();
        Type* baseType = tf.getBasicType(node.type->getBaseType());
        VarAttr* attr = new VarAttr(baseType, false, symTable.getScopeDepth_impl());
        if (!node.dims->empty()) {
        attr->arrayDims.reserve(node.dims->size());
        bool allConst = true;
        for (auto expr : *(node.dims)) {
            if (!apply(*this, *expr)) return false;
            // 检查维度是否整数类型
            auto t = expr->attr.val.value.type->getBaseType();
            if (t != Type_t::INT && t != Type_t::LL) {
                errors.emplace_back("Error: Array dimension must be integer expression."+ std::string("at line ") + std::to_string(node.line_num));
                attr->arrayDims.push_back(-1);
                allConst = false;
                continue;
            }

            if (!expr->attr.val.isConstexpr) {
                attr->arrayDims.push_back(-1);
                allConst = false;
            } else {
                long long dim = (t == Type_t::INT) ?
                                expr->attr.val.getInt() :
                                expr->attr.val.getLL();
                if (dim <= 0) {
                    errors.emplace_back("Error: Array dimension must be > 0."+ std::string("at line ") + std::to_string(node.line_num));
                    dim = 1; 
                }
                attr->arrayDims.push_back(static_cast<int>(dim));
            }
        }
        baseType = tf.getPtrType(baseType); // int[] -> int*
        attr->isConstDecl = node.attr.val.isConstexpr && allConst;
    }
        symTable.addSymbol_impl(node.entry, attr);
        node.attr.val.value.type = baseType;
        node.attr.val.isConstexpr = false;
        return true;
        }
    bool ASTChecker::visit(VarDeclaration& node)
    {
        // TODO(Lab3-1): 实现变量声明的语义检查
        // 遍历声明列表，检查重定义，处理数组维度和初始化，将符号加入符号表
        //TODO("Lab3-1: Implement VarDeclaration semantic checking");
        bool res = true;
        for (auto* decl:*(node.decls)){
            decl->attr.val.value.type = TypeFactory::getInstance().getBasicType(node.type->getBaseType());
            decl->attr.val.isConstexpr = node.isConstDecl;
            res &= apply(*this, *decl);
        }
        return res;
    }
}  // namespace FE::AST
