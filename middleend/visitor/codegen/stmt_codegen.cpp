#include <middleend/visitor/codegen/ast_codegen.h>

namespace ME
{
    void ASTCodeGen::visit(FE::AST::ExprStmt& node, Module* m)
    {
        if (!node.expr) return;
        apply(*this, *node.expr, m);
    }

    void ASTCodeGen::visit(FE::AST::FuncDeclStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成函数定义 IR（形参、入口/结束基本块、返回补丁）
        // 设置函数返回类型与参数寄存器，创建基本块骨架，并生成函数体
        DataType retDt = convert(node.retType);
        std::string fname = node.entry->getName();

        if (!node.body)
        {
            std::vector<DataType> argTypes;
            if (node.params)
            {
                for (auto* p : *node.params)
                {
                    DataType paramDt = convert(p->type);
                    argTypes.push_back(paramDt);
                }
            }
            m->funcDecls.emplace_back(new FuncDeclInst(retDt, fname, argTypes));
            return;
        }

        size_t paramCount = (node.params ? node.params->size() : 0);
        typename FuncDefInst::argList argRegs; 
        size_t maxParamReg = 0;
        for (size_t i = 0; i < paramCount; ++i)
        {
            FE::AST::ParamDeclarator* pd = (*node.params)[i];
            DataType pdt = convert(pd->type);
            size_t preg = i + 1;                      
            maxParamReg = std::max(maxParamReg, preg);
            argRegs.emplace_back(std::make_pair(pdt, getRegOperand(preg)));
        }

        FuncDefInst* fdinst = new FuncDefInst(retDt, fname, argRegs);
        Function* func = new Function(fdinst);
        func->setMaxReg(maxParamReg);
        m->functions.emplace_back(func);

        enterFunc(func);
        Block* entry = createBlock();
        enterBlock(entry);
        name2reg.enterScope();

        for (size_t i = 0; i < paramCount; ++i)
        {
            FE::AST::ParamDeclarator* pd = (*node.params)[i];
            DataType pdt = convert(pd->type);
            size_t paramReg = i + 1;  // 对应上面分配的入参寄存器

            size_t ptrReg = getNewRegId();
            insert(createAllocaInst(pdt, ptrReg));
            insert(createStoreInst(pdt, paramReg, getRegOperand(ptrReg)));
            name2reg.addSymbol(pd->entry, ptrReg);

            FE::AST::VarAttr attr;
            attr.isConstDecl = false;
            attr.type = pd->type;
            attr.scopeLevel = -1;
            reg2attr[ptrReg] = attr;

            // 记录该参数是否为 pointer（供调用/传参时使用）
            paramPtrTab[i] = (pdt == DataType::PTR);
        }

        apply(*this, *node.body, m);

        for (auto& [lbl, block] : func->blocks)
        {
            if (block->insts.empty() || !(block->insts.back()->isTerminator()))
            {
                if (retDt == DataType::VOID)
                {
                    block->insertBack(createRetInst());
                }
                else if (retDt == DataType::I32 || retDt == DataType::I1)
                {
                    block->insertBack(createRetInst(0));
                }
                else if (retDt == DataType::F32)
                {
                    block->insertBack(createRetInst(0.0f));
                }
                else
                {
                    ERROR("Unsupported function return type");
                }
            }
        }

        name2reg.exitScope();
        exitFunc();
        exitBlock();
    }

    void ASTCodeGen::visit(FE::AST::VarDeclStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成变量声明语句 IR（局部变量分配、初始化）
        if (!node.decl) return;
        apply(*this, *node.decl, m)
    }

    void ASTCodeGen::visit(FE::AST::BlockStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成语句块 IR（作用域管理，顺序生成子语句）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement BlockStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::ReturnStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 return 语句 IR（可选返回值与类型转换）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement ReturnStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::WhileStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 while 循环 IR（条件块、循环体与结束块、循环标签）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement WhileStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::IfStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 if/else IR（then/else/end 基本块与条件分支）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement IfStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::BreakStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 break 的无条件跳转至循环结束块
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement BreakStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::ContinueStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 continue 的无条件跳转至循环步进/条件块
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement ContinueStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::ForStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 for 循环 IR（init/cond/body/step 基本块与循环标签）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement ForStmt IR generation");
    }
}  // namespace ME
