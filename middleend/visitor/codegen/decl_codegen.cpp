#include <middleend/visitor/codegen/ast_codegen.h>
#include <debug.h>

namespace ME
{
    void ASTCodeGen::visit(FE::AST::Initializer& node, Module* m)
    {
        (void)m;
        ERROR("Initializer should not appear here, at line %d", node.line_num);
    }
    void ASTCodeGen::visit(FE::AST::InitializerList& node, Module* m)
    {
        (void)m;
        ERROR("InitializerList should not appear here, at line %d", node.line_num);
    }
    void ASTCodeGen::visit(FE::AST::VarDeclarator& node, Module* m)
    {
        (void)m;
        ERROR("VarDeclarator should not appear here, at line %d", node.line_num);
    }
    void ASTCodeGen::visit(FE::AST::ParamDeclarator& node, Module* m)
    {
        (void)m;
        ERROR("ParamDeclarator should not appear here, at line %d", node.line_num);
    }

    void ASTCodeGen::visit(FE::AST::VarDeclaration& node, Module* m)
    {
        // TODO(Lab 3-2): 生成变量声明 IR（alloca、数组零初始化、可选初始化表达式）
        DataType t = convert(node.type);
        for (auto* decl : *(node.decls))
        {
            auto* lval = dynamic_cast<FE::AST::LeftValExpr*>(decl->lval);
            FE::Sym::Entry* entry = lval->entry;

            size_t ptrReg = getNewRegId();
            insert(createAllocaInst(t, ptrReg));
            name2reg.addSymbol(entry, ptrReg);

            reg2attr[ptrReg] = FE::AST::VarAttr{node.type};
            lval2ptr[lval] = getRegOperand(ptrReg);

            if (decl->init)
            {
                if (auto* initDecl = dynamic_cast<FE::AST::Initializer*>(decl->init)) 
                {
                    handleAssign(*lval, *initDecl->init_val, m);
                } else 
                {
                    ERROR("Unsupported initializer node type");
                }
            }
        }
    }
}  // namespace ME
