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
        apply(*this, *node.decl, m);
    }

    void ASTCodeGen::visit(FE::AST::BlockStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成语句块 IR（作用域管理，顺序生成子语句）
        // TODO("Lab3-2: Implement BlockStmt IR generation");
        name2reg.enterScope();
        for (auto* stmt : *(node.stmts)) {
            apply(*this, *stmt, m);
        }
        name2reg.exitScope();
    }

    void ASTCodeGen::visit(FE::AST::ReturnStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 return 语句 IR（可选返回值与类型转换）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement ReturnStmt IR generation");
        DataType retType = curFunc->funcDef->retType;  
        if (!node.retExpr)
        {
            insert(createRetInst());
            return;
        }
        apply(*this, *node.retExpr, m);
        size_t exprReg = getMaxReg();   // 表达式结果寄存器
        DataType exprType = convert(node.retExpr->attr.val.value.type);
        if (exprType != retType)
        {
            auto convs = createTypeConvertInst(exprType, retType, exprReg);
            for (auto* inst : convs)
                insert(inst);
            exprReg = getMaxReg();
        }
        if (retType == DataType::I32 || retType == DataType::I1|| retType == DataType::F32)
        {
            insert(createRetInst(retType, exprReg));
        }
        else if (retType == DataType::VOID)
        {
            ERROR("Void function should not return a value");
        }
        else
        {
            ERROR("Unsupported return type");
        }   
    }

    void ASTCodeGen::visit(FE::AST::WhileStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 while 循环 IR（条件块、循环体与结束块、循环标签）
        // TODO("Lab3-2: Implement WhileStmt IR generation");
        Block* condBlock = createBlock();
        Block* bodyBlock = createBlock();
        Block* endBlock  = createBlock();

        // 首先跳到 cond
        insert(createBranchInst(condBlock->blockId));

        // 将 condBlock 注册进函数
        curFunc->blocks[condBlock->blockId] = condBlock;
        curFunc->blocks[bodyBlock->blockId] = bodyBlock;
        curFunc->blocks[endBlock->blockId]  = endBlock;
        loopStack.push_back(LoopContext{condBlock->blockId, endBlock->blockId });

        // === 生成条件检查 ===
        enterBlock(condBlock);

        apply(*this, *node.cond, m);
        size_t condReg = getMaxReg();

        DataType condType = convert(node.cond->attr.val.value.type);
        if (condType != DataType::I1)
        {
            auto convInsts = createTypeConvertInst(condType, DataType::I1, condReg);
            for (auto* inst : convInsts) insert(inst);
            condReg = getMaxReg();
        }
        insert(createBranchInst(condReg, bodyBlock->blockId, endBlock->blockId));

        enterBlock(bodyBlock);
        apply(*this, *node.body, m);

        if (!curBlock->insts.empty() && !curBlock->insts.back()->isTerminator())
            insert(createBranchInst(condBlock->blockId));
        enterBlock(endBlock);
        loopStack.pop_back();
    }

    void ASTCodeGen::visit(FE::AST::IfStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 if/else IR（then/else/end 基本块与条件分支）
        // TODO("Lab3-2: Implement IfStmt IR generation");
        apply(*this, *node.cond, m);
        size_t condReg = getMaxReg();
        DataType condType = convert(node.cond->attr.val.value.type);
        if (condType != DataType::I1)
        {
            auto convInsts = createTypeConvertInst(condType, DataType::I1, condReg);
            for (auto* inst : convInsts)
                insert(inst);
            condReg = getMaxReg();
        }
        Block* thenBlock = createBlock();
        Block* elseBlock = nullptr;
        Block* endBlock  = createBlock();

        if (node.elseStmt)
            elseBlock = createBlock();

        // 生成条件分支指令
        if (elseBlock)
            insert(createBranchInst(condReg, thenBlock->blockId, elseBlock->blockId));
        else
            insert(createBranchInst(condReg, thenBlock->blockId, endBlock->blockId));

        // 把 block 注册到函数
        curFunc->blocks[thenBlock->blockId] = thenBlock;
        if (elseBlock) curFunc->blocks[elseBlock->blockId] = elseBlock;
        curFunc->blocks[endBlock->blockId] = endBlock;
        // then分支
        enterBlock(thenBlock);
        apply(*this, *node.thenStmt, m);

        if (!curBlock->insts.empty() && !curBlock->insts.back()->isTerminator())
            insert(createBranchInst(endBlock->blockId));

        // else 分支
        if (elseBlock)
        {
            enterBlock(elseBlock);
            apply(*this, *node.elseStmt, m);

            if (!curBlock->insts.empty() && !curBlock->insts.back()->isTerminator())
                insert(createBranchInst(endBlock->blockId));
        }
        enterBlock(endBlock);
    }

    void ASTCodeGen::visit(FE::AST::BreakStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 break 的无条件跳转至循环结束块
        // TODO("Lab3-2: Implement BreakStmt IR generation");
        if (loopStack.empty())
            ERROR("break used outside of loop");
        size_t target = loopStack.back().endLabel;
        insert(createBranchInst(target));
        // break 后当前 block 不再继续执行，因此需要新建一个 block 收尾
        Block* nextBlock = createBlock();
        curFunc->blocks[nextBlock->blockId] = nextBlock;
        enterBlock(nextBlock);
    }

    void ASTCodeGen::visit(FE::AST::ContinueStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 continue 的无条件跳转至循环步进/条件块
        // TODO("Lab3-2: Implement ContinueStmt IR generation");
        if (loopStack.empty())
            ERROR("break used outside of loop");
        size_t target = loopStack.back().condLabel;
        insert(createBranchInst(target));
        // continue
        Block* nextBlock = createBlock();
        curFunc->blocks[nextBlock->blockId] = nextBlock;
        enterBlock(nextBlock);
    }

    void ASTCodeGen::visit(FE::AST::ForStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成 for 循环 IR（init/cond/body/step 基本块与循环标签）
        // TODO("Lab3-2: Implement ForStmt IR generation");
        Block* condBlock = createBlock();
        Block* bodyBlock = createBlock();
        Block* stepBlock = createBlock();
        Block* endBlock  = createBlock();

        curFunc->blocks[condBlock->blockId] = condBlock;
        curFunc->blocks[bodyBlock->blockId] = bodyBlock;
        curFunc->blocks[stepBlock->blockId] = stepBlock;
        curFunc->blocks[endBlock->blockId]  = endBlock;
        if (node.init) {
            apply(*this, *node.init, m);
        }
        insert(createBranchInst(condBlock->blockId));
        // 处理循环条件
        enterBlock(condBlock);
        size_t condReg = static_cast<size_t>(-1);
        DataType condType = DataType::I1;
        if (node.cond) {
            apply(*this, *node.cond, m);
            condReg = getMaxReg();
            condType = convert(node.cond->attr.val.value.type);

            // 将 cond 转为 bool
            if (condType != DataType::I1) {
                auto convInsts = createTypeConvertInst(condType, DataType::I1, condReg);
                for (auto inst: convInsts) insert(inst);
                condReg = getMaxReg();
            }

            insert(createBranchInst(condReg, bodyBlock->blockId, endBlock->blockId));
        } else {
            // 无条件，视为 true
            insert(createBranchInst(bodyBlock->blockId));
        }
        // 处理循环体
        enterBlock(bodyBlock);
        loopStack.push_back({ stepBlock->blockId, endBlock->blockId });
        if (node.body)
            apply(*this, *node.body, m);
        insert(createBranchInst(stepBlock->blockId));
        // 返回步进
        enterBlock(stepBlock);
        if (node.step)
            apply(*this, *node.step, m);
        insert(createBranchInst(condBlock->blockId));
        loopStack.pop_back();
        enterBlock(endBlock);
    }
}  // namespace ME
