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
        //TODO("Lab3-1: Implement VarDeclarator semantic checking");
        auto* lval = dynamic_cast<LeftValExpr*>(node.lval);
        bool res = true;
        if (lval->indices) {
            for (auto* index_expr : *(lval->indices)) {
                res &= apply(*this, *index_expr);
            }
        }
        if(node.init) {
            res = apply(*this, *(node.init)); 
            node.attr = node.lval->attr;
                return false;
        }
        try {
            symTable.addSymbol_impl(lval->entry, VarAttr());
        }
        catch (const std::runtime_error& e) {
            errors.push_back(std::string("Error: Redefinition of variable '") + lval->entry->getName() + "'.");
            return false;
        }
    }

    bool ASTChecker::visit(ParamDeclarator& node)
    {
        // TODO(Lab3-1): 实现函数形参的语义检查
        // 检查形参重定义，处理数组形参的类型退化，将形参加入符号表
        //TODO("Lab3-1: Implement ParamDeclarator semantic checking");
        if (symTable.getlocalSymbol_impl(node.entry)) {
            errors.emplace_back("Error: Redefinition of parameter '" + node.entry->getName() + "'.");
            return false;
        }
        Type* baseType = node.type;
        VarAttr* attr = new VarAttr(baseType, false, symTable.getScopeDepth_impl());
        if (!node.dims->empty()) {
            baseType = FE::AST::TypeFactory::getInstance().getPtrType(baseType);
            for (auto expr : *(node.dims)) {
                bool hasError = false;
                ExprValue dimVal = typeInfer(expr->attr.val, expr->attr.op, *expr, hasError);
                if (hasError || !dimVal.isConstexpr) {
                    // 非常量维度用 -1 标记
                    attr->arrayDims.push_back(-1);
                } else {
                    // 编译期常量维度
                    attr->arrayDims.push_back(dimVal.value.getInt());
                }
            }
        }
        symTable.addSymbol_impl(node.entry, attr);
        node.attr.val.value.type = baseType;
        return true;
        }
    bool ASTChecker::visit(VarDeclaration& node)
    {
        // TODO(Lab3-1): 实现变量声明的语义检查
        // 遍历声明列表，检查重定义，处理数组维度和初始化，将符号加入符号表
        //TODO("Lab3-1: Implement VarDeclaration semantic checking");
        bool res = true;
        for (auto* decl:*(node.decls)){
            decl->attr.val.value.type = node.type;
            decl->attr.val.isConstexpr = node.isConstDecl;
            res &= apply(*this, *decl);
        }
        return res;
    }
}  // namespace FE::AST
