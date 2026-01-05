#include <frontend/ast/visitor/sementic_check/ast_checker.h>
#include <debug.h>

namespace FE::AST
{
    bool ASTChecker::visit(ExprStmt& node)
    {
        // 示例实现：表达式语句的语义检查
        // 空表达式直接通过，否则访问内部表达式
        if (!node.expr) return true;
        return apply(*this, *node.expr);
    }

    bool ASTChecker::visit(FuncDeclStmt& node)
    {
        // TODO(Lab3-1): 实现函数声明的语义检查
        // 检查作用域，记录函数信息，处理形参和函数体，检查返回语句
        //TODO("Lab3-1: Implement FuncDeclStmt semantic checking");
        bool res = true;
        if (symTable.getlocalSymbol_impl(node.entry)) {
            errors.emplace_back("Error: Redefinition of function '" + node.entry->getName() + "'." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        VarAttr* funcAttr = new VarAttr(node.retType, false, symTable.getScopeDepth_impl());
        symTable.addSymbol_impl(node.entry, funcAttr);
        funcDecls[node.entry] = &node;
        // main 函数标记
        if (node.entry->getName() == "main") {
            mainExists = true;
            if (node.retType->getBaseType() != Type_t::INT) {
                errors.emplace_back("Error: main function must return int." + std::string("at line ") + std::to_string(node.line_num));
                res = false;
            }
        }
        symTable.enterScope_impl();
        curFuncRetType = node.retType;
        funcHasReturn = false;

        for (auto* param : *(node.params)) {
            res &= apply(*this, *param);
        }

        res &= apply(*this, *(node.body));

        Type_t retBase = curFuncRetType->getBaseType();
        if (retBase != Type_t::VOID && !funcHasReturn&&node.entry->getName()!="main") {
            errors.emplace_back("Error: Non-void function '" + node.entry->getName() + "' must return a value." + std::string("at line ") + std::to_string(node.line_num));
            res = false;
        }

        symTable.exitScope_impl();

        // 清除上下文信息
        curFuncRetType= nullptr;
        funcHasReturn = false;

        return res;
    }

    bool ASTChecker::visit(VarDeclStmt& node)
    {
        // TODO(Lab3-1): 实现变量声明语句的语义检查
        // 空声明直接通过，否则委托给变量声明处理
        //TODO("Lab3-1: Implement VarDeclStmt semantic checking");
        if (!node.decl) return true;
        return apply(*this, *(node.decl));
    }

    bool ASTChecker::visit(BlockStmt& node)
    {
        // TODO(Lab3-1): 实现块语句的语义检查
        // 进入新作用域，逐条访问语句，退出作用域
        //TODO("Lab3-1: Implement BlockStmt semantic checking");
        symTable.enterScope_impl();
        bool res = true;
        for (auto* stmt : *(node.stmts)) {
            ASSERT(stmt && "Null stmt in BlockStmt");
            res &= apply(*this, *stmt) && res;
        }
        symTable.exitScope_impl();
        return res;
    }

    bool ASTChecker::visit(ReturnStmt& node)
    {
        // TODO(Lab3-1): 实现返回语句的语义检查
        // 设置返回标记，检查作用域，检查返回值类型匹配
        //TODO("Lab3-1: Implement ReturnStmt semantic checking");
        funcHasReturn = true;
        bool res = true;
        if (node.retExpr) {
            res &= apply(*this, *(node.retExpr));
            Type* retType = node.retExpr->attr.val.value.type;
            if (!retType) {
                errors.emplace_back("Error: Return expression has no type." + std::string("at line ") + std::to_string(node.line_num));
                return false;
            }
            if (retType->getBaseType() != curFuncRetType->getBaseType()) {
                errors.emplace_back("Error: Return type mismatch." + std::string("at line ") + std::to_string(node.line_num));
                return false;
            }
        }
        else{
            if (curFuncRetType->getBaseType() != Type_t::VOID) {
                errors.emplace_back("Error: Non-void function must return a value." + std::string("at line ") + std::to_string(node.line_num));
                return false;
            }
        }
        return res;
    }

    bool ASTChecker::visit(WhileStmt& node)
    {
        // TODO(Lab3-1): 实现while循环的语义检查
        // 检查作用域，访问条件表达式，管理循环深度，访问循环体
        //TODO("Lab3-1: Implement WhileStmt semantic checking");
        bool res = true;
        res &= apply(*this, *(node.cond));
        Type* condType = node.cond->attr.val.value.type;
        if (!condType) {
            errors.emplace_back("Error: Condition expression has no type." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        Type_t condBase = condType->getBaseType();
        if (condBase != Type_t::BOOL&& condBase != Type_t::INT && condBase != Type_t::LL&& condBase != Type_t::FLOAT) {
            errors.emplace_back("Error: Condition expression must be of type bool" + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        if (!node.body) return true;
        loopDepth++;
        symTable.enterScope_impl();
        res &= apply(*this, *(node.body));
        symTable.exitScope_impl();
        loopDepth--;
        return res;
    }

    bool ASTChecker::visit(IfStmt& node)
    {
        // TODO(Lab3-1): 实现if语句的语义检查
        // 检查作用域，访问条件表达式，分别访问then和else分支
        //TODO("Lab3-1: Implement IfStmt semantic checking");
        bool res = true;
        res &= apply(*this, *(node.cond));
        Type* condType = node.cond->attr.val.value.type;
        if (!condType) {
            errors.emplace_back("Error: Condition expression has no type." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        Type_t condBase = condType->getBaseType();
        if (condBase != Type_t::BOOL&& condBase != Type_t::INT && condBase != Type_t::LL&& condBase != Type_t::FLOAT) {
            errors.emplace_back("Error: Condition expression must be of type bool" + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        if (!node.thenStmt) return true;
        symTable.enterScope_impl();
        res &= apply(*this, *(node.thenStmt));
        symTable.exitScope_impl();
        if (node.elseStmt) {
            symTable.enterScope_impl();
            res &= apply(*this, *(node.elseStmt));
            symTable.exitScope_impl();
        }
        return res;
    }

    bool ASTChecker::visit(BreakStmt& node)
    {
        // TODO(Lab3-1): 实现break语句的语义检查
        // 检查是否在循环内使用
        //TODO("Lab3-1: Implement BreakStmt semantic checking");
        if (loopDepth == 0) {
            errors.emplace_back("Error: 'break' statement not within a loop." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        return true;
    }

    bool ASTChecker::visit(ContinueStmt& node)
    {
        // TODO(Lab3-1): 实现continue语句的语义检查
        // 检查是否在循环内使用
        //TODO("Lab3-1: Implement ContinueStmt semantic checking");
        if (loopDepth == 0) {
            errors.emplace_back("Error: 'continue' statement not within a loop." + std::string("at line ") + std::to_string(node.line_num));
            return false;
        }
        return true;
    }

    bool ASTChecker::visit(ForStmt& node)
    {
        // TODO(Lab3-1): 实现for循环的语义检查
        // 检查作用域，访问初始化、条件、步进表达式，管理循环深度
        //TODO("Lab3-1: Implement ForStmt semantic checking");
        bool res = true;
        symTable.enterScope_impl();
        if (node.init) {
            res &= apply(*this, *(node.init));  
        }
        if (node.cond) {
            res &= apply(*this, *(node.cond));
            Type* condType = node.cond->attr.val.value.type;
            if (!condType) {
                errors.emplace_back("Error: Condition expression has no type." + std::string("at line ") + std::to_string(node.line_num));
                return false;
            }
            Type_t condBase = condType->getBaseType();
            if (condBase != Type_t::BOOL&& condBase != Type_t::INT && condBase != Type_t::LL&& condBase != Type_t::FLOAT) {
                errors.emplace_back("Error: Condition expression must be of type bool" + std::string("at line ") + std::to_string(node.line_num));
                return false;
            }
        }
        if (node.step) {
            res &= apply(*this, *(node.step));
        }
        if (!node.body) return true;
        loopDepth++;
        res &= apply(*this, *(node.body));
        loopDepth--;
        symTable.exitScope_impl();
        return res;
    }
}  // namespace FE::AST
