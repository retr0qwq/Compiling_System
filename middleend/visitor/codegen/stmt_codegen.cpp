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
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement FuncDeclStmt IR generation");
    }

    void ASTCodeGen::visit(FE::AST::VarDeclStmt& node, Module* m)
    {
        // TODO(Lab 3-2): 生成变量声明语句 IR（局部变量分配、初始化）
        (void)node;
        (void)m;
        TODO("Lab3-2: Implement VarDeclStmt IR generation");
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
        Block* initBlock = curBlock;
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
