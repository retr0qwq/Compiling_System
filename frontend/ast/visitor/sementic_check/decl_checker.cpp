#include <frontend/ast/visitor/sementic_check/ast_checker.h>
#include <debug.h>
#include <functional>
#include <limits>
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
        // 处理数组维度
        if (lval->indices && !lval->indices->empty()) {
            varAttr->arrayDims.clear();
            for(auto* expr : *(lval->indices)) {
                if (!apply(*this, *expr)) {
                    delete varAttr;
                    return false;
                }
                Type_t idxType = expr->attr.val.value.type->getBaseType();
                if (idxType != Type_t::INT && idxType != Type_t::LL && idxType != Type_t::BOOL) {
                    errors.emplace_back("Error: Array index must be of integer type." + std::string("at line ") + std::to_string(node.line_num));
                    delete varAttr;
                    return false;
                }
                // 记录维度信息
                if (expr->attr.val.isConstexpr) {
                    int dimSize = 0;
                    if (idxType == Type_t::INT) dimSize = expr->attr.val.getInt();
                    else if (idxType == Type_t::LL) {
                        long long dimLL = expr->attr.val.getLL();
                        if (dimLL > static_cast<long long>(std::numeric_limits<int>::max())) {
                            errors.emplace_back("Error: Array dimension size too large at line " + std::to_string(node.line_num));
                            delete varAttr;
                            return false;
                        }
                        dimSize = static_cast<int>(dimLL);
                    }
                    else if  (idxType == Type_t::LL ) dimSize = static_cast<int>(expr->attr.val.getLL());
                    else if (idxType == Type_t::BOOL) dimSize = expr->attr.val.getBool() ? 1 : 0;
                    varAttr->arrayDims.push_back(dimSize);
                } else {
                    errors.emplace_back("Error: Array dimension must be a constant expression." + std::string("at line ") + std::to_string(node.line_num));
                    return false;
                }
            }
        }
        symTable.addSymbol_impl(entry, varAttr); 
        node.attr.val=node.lval->attr.val;
        if (symTable.isGlobalScope_impl()) {
            glbSymbols[entry] = *symTable.getSymbol_impl(entry);
        }
        if (node.init) {
            res &= apply(*this, *node.init);
            // 类型检查          
            Type* lhsType = varType;
            Type* rhsType = node.init->attr.val.value.type;

            Type_t lhsBase = lhsType->getBaseType();
            Type_t rhsBase = rhsType->getBaseType();
            if (lhsType->getTypeGroup() == TypeGroup::POINTER ||rhsType->getTypeGroup() == TypeGroup::POINTER) {
                if (lhsBase != rhsBase||(lhsType->getTypeGroup() != rhsType->getTypeGroup())) {
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
            node.lval->attr.val.isConstexpr = node.init->attr.val.isConstexpr;
            std::vector<VarValue> flattened;
            size_t totalSize = 1;
            for (size_t dim : varAttr->arrayDims) totalSize *= dim;
            std::function<bool(InitDecl*, int)> fill = [&](InitDecl* initNode, size_t dim) -> bool {
                if (initNode->singleInit) {
                    // 标量初始化
                    if (dim != varAttr->arrayDims.size()) {
                        errors.emplace_back("Error: Scalar initializer used for non-scalar array at line "
                            + std::to_string(node.line_num));
                        return false;
                    }
                    auto* initExpr = static_cast<Initializer*>(initNode)->init_val;
                    if (!apply(*this, *initExpr)) return false;

                    Type_t baseType = initExpr->attr.val.value.type->getBaseType();
                    if (baseType == Type_t::INT)      flattened.emplace_back(initExpr->attr.val.getInt());
                    else if (baseType == Type_t::LL)  flattened.emplace_back(initExpr->attr.val.getLL());
                    else if (baseType == Type_t::BOOL)flattened.emplace_back(initExpr->attr.val.getBool() ? 1 : 0);
                    else if (baseType == Type_t::FLOAT)flattened.emplace_back(initExpr->attr.val.getFloat());
                    else {
                        errors.emplace_back("Error: Unsupported initializer type at line " + std::to_string(node.line_num));
                        return false;
                    }
                    return true;
                }
             while (!initNode->singleInit) {
                auto* listNode = static_cast<InitializerList*>(initNode);
                if (varAttr->arrayDims[dim] > 1)
                    break;

                if (listNode->init_list->size() == 1) {
                    initNode = (*listNode->init_list)[0];
                    continue;
                }

                break;
            }
                // 初始化列表
                auto* listNode = static_cast<InitializerList*>(initNode);
                size_t subDimSize = 1;
                for (size_t i = dim + 1; i < varAttr->arrayDims.size(); i++)
                    subDimSize *= varAttr->arrayDims[i];

                size_t maxElements = varAttr->arrayDims[dim];
                size_t count = 0;

                for (auto* subInit : *(listNode->init_list)) {
                    if (count >= maxElements) {
                        errors.emplace_back("Error: Too many initializers at line "+ std::to_string(node.line_num));
                        return false;
                    }
                    if (!fill(subInit, dim + 1)) return false;
                    count++;
                }

                // 自动补零
                size_t shouldSize = flattened.size() + (maxElements - count) * subDimSize;
                while (flattened.size() < shouldSize)
                    flattened.emplace_back(0);

                return true;
            };

            if (!fill(node.init, 0)) return false;
            if (varAttr->arrayDims.empty()) {
                if (flattened.size() != 1) {
                    errors.emplace_back("Error: Too many initializers for scalar variable at line "+ std::to_string(node.line_num));
                    return false;
                }
            }
            else {
                if (flattened.size() > totalSize) {
                    errors.emplace_back("Error: Initializers exceed array size at line " + std::to_string(node.line_num));
                    return false;
                }
            }
            // 存入属性
            varAttr->initList = std::move(flattened);
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
        if (node.dims && !node.dims->empty()) {
            attr->arrayDims.reserve(node.dims->size());
            for (auto expr : *(node.dims)) {
                if (!apply(*this, *expr)) return false;
                // 检查维度是否整数类型
                auto t = expr->attr.val.value.type->getBaseType();
                if (t != Type_t::INT && t != Type_t::LL&& t != Type_t::BOOL) {
                    errors.emplace_back("Error: Array dimension must be integer expression."+ std::string("at line ") + std::to_string(node.line_num));
                    attr->arrayDims.push_back(-1);
                    continue;
                }

                if (!expr->attr.val.isConstexpr) {
                    attr->arrayDims.push_back(-1);
                    errors.emplace_back("Error: Array dimension must be a constant expression."+ std::string("at line ") + std::to_string(node.line_num));
                } else {
                    long long dim = (t == Type_t::INT) ?
                                    expr->attr.val.getInt() :
                                    expr->attr.val.getLL();
                    attr->arrayDims.push_back(static_cast<int>(dim));
                }
            }
            baseType = tf.getPtrType(baseType); // int[] -> int*
            attr->isConstDecl = false;
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
