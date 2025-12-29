#include <middleend/pass/mem2reg.h>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <stack>
using namespace ME;
void Mem2Reg::runOnModule(Module& module)
{
    for (auto* func : module.functions)
        runOnFunction(*func);
}
void Mem2Reg::runOnFunction(Function& function)
{
    Mem2Reg_1(function);
    Mem2Reg_2(function);
    Mem2Reg_3(function);
}

bool Mem2Reg::Mem2Reg_1(Function& function)
{
    std::unordered_map<AllocaInst*, bool> hasLoad;
    std::unordered_map<Operand*, AllocaInst*> reg2alloca;
    // 先找到所有的alloca指令
    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::ALLOCA)
            {
                auto* allocaInst = static_cast<AllocaInst*>(inst);
                reg2alloca[allocaInst->res] = allocaInst;
                hasLoad[allocaInst] = false;
            }
        }
    }
    // 再找load指令
    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            if (inst->opcode != Operator::LOAD)
                continue;

            auto* loadInst = static_cast<LoadInst*>(inst);
            auto it = reg2alloca.find(loadInst->ptr);
            if (it != reg2alloca.end())
            {
                hasLoad[it->second] = true;
            }
        }
    }

    std::vector<Instruction*> toDelete;
    // 找到所有未被load的alloca指令及其相关的store指令
    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            // alloca
            if (inst->opcode == Operator::ALLOCA)
            {
                auto* allocaInst = static_cast<AllocaInst*>(inst);
                if (!hasLoad[allocaInst])
                    toDelete.push_back(inst);
            }
            // store
            else if (inst->opcode == Operator::STORE)
            {
                auto* storeInst = static_cast<StoreInst*>(inst);
                auto it = reg2alloca.find(storeInst->ptr);
                if (it != reg2alloca.end() && !hasLoad[it->second])
                    toDelete.push_back(inst);
            }
        }
    }

    if (toDelete.empty())
        return false;
    // 删除指令
    Analysis::AM.invalidate(function);
    size_t delIdx = 0;
    for (auto& [bid, block] : function.blocks)
    {
        std::deque<Instruction*> newInsts;
        newInsts.resize(0);

        for (auto* inst : block->insts)
        {
            if (delIdx < toDelete.size() && inst == toDelete[delIdx]) {
                ++delIdx;   // 跳过（删除）
            } else {
                newInsts.push_back(inst);
            }
        }

        block->insts.swap(newInsts);
    }

    return true;
}

bool Mem2Reg::Mem2Reg_2(Function& function)
{
    std::unordered_map<Operand*, AllocaInst*> reg2alloca;
    std::unordered_map<AllocaInst*, Block*> allocaBlock;
    std::unordered_map<AllocaInst*, bool> singleBlock;
    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::ALLOCA)
            {
                auto* a = static_cast<AllocaInst*>(inst);
                reg2alloca[a->res] = a;
                allocaBlock[a] = block;
                singleBlock[a] = true;
            }
        }
    }
    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {

            if (inst->opcode == Operator::LOAD)
            {
                auto* l = static_cast<LoadInst*>(inst);
                auto it = reg2alloca.find(l->ptr);
                if (it != reg2alloca.end())
                {
                    if (block != allocaBlock[it->second])
                        singleBlock[it->second] = false;
                }
            }
            // 检查 Store 
            else if (inst->opcode == Operator::STORE)
            {
                auto* s = static_cast<StoreInst*>(inst);
                auto it = reg2alloca.find(s->ptr); 
                if (it != reg2alloca.end())
                {
                    if (block != allocaBlock[it->second])
                        singleBlock[it->second] = false;
                }
            }
        }
    }
    bool changed = false;
    for (auto& [allocaInst, block] : allocaBlock)
    {
        if (!singleBlock[allocaInst]) continue;

        Operand* currentVal = nullptr;
        bool hasDef = false;
        Instruction* zeroDefInst = nullptr; 
        std::vector<Instruction*> toDelete;
        RegMap renameMap; // oldReg -> newReg

        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::STORE)
            {
                auto* s = static_cast<StoreInst*>(inst);
                if (s->ptr == allocaInst->res)
                {
                    currentVal = s->val;
                    hasDef = true;
                    toDelete.push_back(inst);
                }
            }
            else if (inst->opcode == Operator::LOAD)
            {
                auto* l = static_cast<LoadInst*>(inst);
                if (l->ptr == allocaInst->res)
                {
                    if (hasDef)
                    {
                        renameMap[l->res->getRegNum()] = currentVal->getRegNum();
                        toDelete.push_back(inst);
                    }
                    else
                    {
                        if (currentVal == nullptr)
                        {
                            Operand* zeroReg = getImmeI32Operand(0);
                            zeroDefInst = new ArithmeticInst(Operator::ADD, DataType::I32, zeroReg, zeroReg, l->res);
                            currentVal = zeroReg;
                            renameMap[l->res->getRegNum()] = currentVal->getRegNum();
                            toDelete.push_back(inst);
                        }
                    }
                }
            }
            else if (inst->opcode == Operator::ALLOCA)
            {
                if (inst == allocaInst)
                    toDelete.push_back(inst);
            }
        }
        RegRename Renamer;
        for (auto* inst : block->insts)
        {
            apply(Renamer, *inst, renameMap);
        }
        if (!toDelete.empty())
        {
            changed = true;
            Analysis::AM.invalidate(function);

            std::deque<Instruction*> newInsts;
            if (zeroDefInst)
                newInsts.push_back(zeroDefInst);
            size_t delIdx = 0;
            newInsts.resize(0);

            for (auto* inst : block->insts)
            {
                if (delIdx < toDelete.size() && inst == toDelete[delIdx]) {
                    ++delIdx;   // 跳过（删除）
                } else {
                    newInsts.push_back(inst);
                }
            }
            block->insts.swap(newInsts);
        }
    }
    return changed;
}


bool Mem2Reg::Mem2Reg_3(Function& function)
{
    using namespace Analysis;

    CFG* cfg = AM.get<CFG>(function);
    DomInfo* domInfo = AM.get<DomInfo>(function);
    auto& df = domInfo->getDomFrontier();
    auto& domTree = domInfo->getDomTree();

    std::unordered_map<Operand*, AllocaInst*> reg2alloca;
    std::unordered_map<AllocaInst*, Block*> allocaDefBlock;
    std::unordered_map<AllocaInst*, Operand*> exitVal;

    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::ALLOCA)
            {
                auto* a = static_cast<AllocaInst*>(inst);
                allocaDefBlock[a] = block;
                reg2alloca[a->res] = a;
            }
        }
    }

    std::unordered_map<AllocaInst*, std::set<Block*>> allocaUses;

    for (auto& [bid, block] : function.blocks)
    {
        for (auto* inst : block->insts)
        {
            Operand* ptr = nullptr;
            if (inst->opcode == Operator::LOAD)
                ptr = static_cast<LoadInst*>(inst)->ptr;
            else if (inst->opcode == Operator::STORE)
                ptr = static_cast<StoreInst*>(inst)->ptr;

            if (ptr)
            {
                auto it = reg2alloca.find(ptr);
                if (it != reg2alloca.end())
                    allocaUses[it->second].insert(block);
            }
        }
    }

    bool changed = false;

    std::unordered_map<AllocaInst*, std::set<Block*>> hasPhi;
    std::unordered_map<PhiInst*, AllocaInst*> phiToAlloca;

    for (auto& [allocaInst, useBlocks] : allocaUses)
    {
        std::set<Block*> work = useBlocks;
        while (!work.empty())
        {
            auto it = work.begin();
            Block* b = *it;
            work.erase(it);

            if (b->blockId >= df.size()) continue; // 边界检查

            for (int dfBid : df[b->blockId])
            {
                // 安全获取块，避免 [] 产生 nullptr
                auto itBlock = cfg->id2block.find(dfBid);
                if (itBlock == cfg->id2block.end()) continue;
                
                Block* frontierBlock = itBlock->second;
                if (hasPhi[allocaInst].count(frontierBlock)) continue;

                RegOperand* phiRes = OperandFactory::getInstance().getRegOperand(function.getNewRegId()); 
                PhiInst* phi = new PhiInst(allocaInst->dt, phiRes);

                frontierBlock->insts.push_front(phi);
                hasPhi[allocaInst].insert(frontierBlock);
                phiToAlloca[phi] = allocaInst;
                work.insert(frontierBlock);
            }
        }
    }

    std::unordered_map<AllocaInst*, std::stack<Operand*>> valStack;
    for (auto& [allocaInst, _] : allocaDefBlock)
        valStack[allocaInst] = std::stack<Operand*>();

    std::function<void(Block*, RegMap)> renameBlock;
    renameBlock = [&](Block* block, RegMap renameMap) 
    {
        if (!block) return;

        std::unordered_map<AllocaInst*, int> pushCount;
        RegRename Renamer;
        // 1. 处理本块 PHI 的定义 (Push to Stack)
        for (auto* inst : block->insts) {
            if (inst->opcode == Operator::PHI) {
                auto* phi = static_cast<PhiInst*>(inst);
                if (phiToAlloca.count(phi)) {
                    valStack[phiToAlloca[phi]].push(phi->res);
                    pushCount[phiToAlloca[phi]]++;
                }
            }
        }

        // 2. 处理 Load/Store (更新 renameMap 和 valStack)
        for (auto it = block->insts.begin(); it != block->insts.end(); ) {
            auto* inst = *it;
            if (inst->opcode != Operator::PHI) {
                apply(Renamer, *inst, renameMap);
            }
            if (inst->opcode == Operator::LOAD) {
                auto* l = static_cast<LoadInst*>(inst);
                if (reg2alloca.count(l->ptr)) {
                    AllocaInst* ai = reg2alloca[l->ptr];
                    // 如果栈为空，给一个常量 0 操作数，不要给 allocaInst->res
                    Operand* curVal = valStack[ai].empty() ? 
                                    OperandFactory::getInstance().getImmeI32Operand(0) : valStack[ai].top();
                    
                    renameMap[l->res->getRegNum()] = curVal->getRegNum();
                    it = block->insts.erase(it); // 只有确认是 mem2reg 的 load 才能删
                    continue;
                }
            } else if (inst->opcode == Operator::STORE) {
                auto* s = static_cast<StoreInst*>(inst);
                if (reg2alloca.count(s->ptr)) {
                    AllocaInst* ai = reg2alloca[s->ptr];
                    valStack[ai].push(s->val);
                    pushCount[ai]++;
                    it = block->insts.erase(it);
                    continue;
                }
            }
            ++it;
        }
        // --- 重点修改 1：在递归子节点前，填充 CFG 后继的 PHI ---
        // 此时 valStack.top() 正好代表了变量在当前块结束时的最新值
        if (block->blockId < cfg->G.size()) {
            for (auto* succBlock : cfg->G[block->blockId]) {
                for (auto* inst : succBlock->insts) {
                    if (inst->opcode != Operator::PHI) break;
                    
                    auto* phi = static_cast<PhiInst*>(inst);
                    if (phiToAlloca.count(phi)) {
                        AllocaInst* ai = phiToAlloca[phi];
                        Operand* val = valStack[ai].empty() ? OperandFactory::getInstance().getImmeI32Operand(0) : valStack[ai].top();
                        
                        phi->addIncoming(val, OperandFactory::getInstance().getLabelOperand(block->blockId));
                    }
                }
            }
        }

        // --- 重点修改 2：递归支配树子节点，传递 renameMap ---
        if (block->blockId < domTree.size()) {
            for (int childBid : domTree[block->blockId]) {
                if (cfg->id2block.count(childBid)) {
                    renameBlock(cfg->id2block[childBid], renameMap);
                }
            }
        }

        // 4. 弹出栈 (回溯)
        for (auto& [allocaInst, count] : pushCount) {
            for (int i = 0; i < count; ++i) {
                valStack[allocaInst].pop();
            }
        }
    };
    const auto& immDom = domInfo->getImmDom();
    // 安全的入口调用
    for (auto& [bid, block] : function.blocks)
    {
        if (bid < immDom.size() && immDom[bid] == -1)
        {
            renameBlock(block, RegMap{});
        }
    }


    // 清理原始指令
    for (auto& [bid, block] : function.blocks)
    {
        std::deque<Instruction*> newInsts;
        for (auto* inst : block->insts)
        {
            bool remove = false;
            if (inst->opcode == Operator::ALLOCA) {
                if (reg2alloca.count(static_cast<AllocaInst*>(inst)->res)) remove = true;
            } else if (inst->opcode == Operator::LOAD) {
                if (reg2alloca.count(static_cast<LoadInst*>(inst)->ptr)) remove = true;
            } else if (inst->opcode == Operator::STORE) {
                if (reg2alloca.count(static_cast<StoreInst*>(inst)->ptr)) remove = true;
            }
            
            if (!remove) newInsts.push_back(inst);
        }
        block->insts.swap(newInsts);
    }

    if (changed)
        AM.invalidate(function);

    return changed;
}