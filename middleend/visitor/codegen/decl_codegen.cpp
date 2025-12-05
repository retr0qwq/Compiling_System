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

        for (auto* decl : node.decls)
        {
            FE::Sym::Entry* entry = decl->entry;
            FE::AST::VarAttr attr = reg2attr[getNewRegId()]; 

            size_t ptrReg = getNewRegId();
            AllocaInst* alloc = createAllocaInst(t, ptrReg);
            insert(alloc);

            name2reg.addSymbol(entry, ptrReg);

            if (decl->initializer)
            {
                apply(*this, *decl->initializer, m);
                size_t valReg = getMaxReg();

                DataType fromT = convert(decl->initializer->attr.val.value.type);
                if (fromT != t)
                {
                    auto convInsts = createTypeConvertInst(fromT, t, valReg);
                    for (auto* inst : convInsts)
                        insert(inst);
                    valReg = getMaxReg();
                }
                insert(createStoreInst(t, valReg, getRegOperand(ptrReg)));
            }
        }
    }
}  // namespace ME
