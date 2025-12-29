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

    std::function<void(Block*)> renameBlock;
    renameBlock = [&](Block* block)
    {
        if (!block) return; // 关键安全检查：防止空指针访问

        std::unordered_map<AllocaInst*, int> pushCount; // 记录本块压栈次数
        RegMap renameMap;

        // 1. 处理 PHI 定义
        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::PHI)
            {
                auto* phi = static_cast<PhiInst*>(inst);
                auto it = phiToAlloca.find(phi);
                if (it != phiToAlloca.end())
                {
                    valStack[it->second].push(phi->res);
                    pushCount[it->second]++;
                }
            }
        }

        // 2. 处理 Load/Store
        for (auto* inst : block->insts)
        {
            if (inst->opcode == Operator::LOAD)
            {
                auto* l = static_cast<LoadInst*>(inst);
                auto it = reg2alloca.find(l->ptr);
                if (it != reg2alloca.end())
                {
                    AllocaInst* allocaInst = it->second;
                    Operand* val = valStack[allocaInst].empty() ? allocaInst->res : valStack[allocaInst].top();
                    renameMap[l->res->getRegNum()] = val->getRegNum();
                    changed = true;
                }
            }
            else if (inst->opcode == Operator::STORE)
            {
                auto* s = static_cast<StoreInst*>(inst);
                auto it = reg2alloca.find(s->ptr);
                if (it != reg2alloca.end())
                {
                    valStack[it->second].push(s->val);
                    pushCount[it->second]++;
                    changed = true;
                }
            }
        }

        // 应用替换
        RegRename Renamer;
        for (auto* inst : block->insts)
        {   
            if (!inst) continue; 
            if (inst->opcode == Operator::ALLOCA) continue;
            if (inst->opcode == Operator::PHI)
            {
                auto* phi = static_cast<PhiInst*>(inst);
                if (phiToAlloca.count(phi)) continue;
            }
            apply(Renamer, *inst, renameMap);
        }

        // 3. 填充后继块 PHI (Safe Access)
        if (block->blockId < cfg->G.size())
        {
            for (auto* succBlock : cfg->G[block->blockId])
            {
                if (!succBlock) continue;

                for (auto* inst : succBlock->insts)
                {
                    if (inst->opcode != Operator::PHI) continue;

                    auto* phi = static_cast<PhiInst*>(inst);
                    auto it = phiToAlloca.find(phi);
                    if (it == phiToAlloca.end()) continue;

                    AllocaInst* allocaInst = it->second;

                    // 直接获取栈顶值或 fallback 到原始 alloca 寄存器
                    Operand* val = valStack[allocaInst].empty() ? allocaInst->res : valStack[allocaInst].top();
                    LabelOperand* label = OperandFactory::getInstance().getLabelOperand(block->blockId);

                    phi->addIncoming(val, label);
                }
            }
        }


        // 4. 递归遍历支配树子节点 (Safe Access)-
        if (block->blockId < domTree.size())
        {
            for (int childBid : domTree[block->blockId])
            {
                auto it = cfg->id2block.find(childBid);
                if (it != cfg->id2block.end())
                    renameBlock(it->second);
            }
        }

        // 5. 弹出栈 (根据计数精确弹出)
        for (auto& [allocaInst, count] : pushCount)
        {
            for (int i = 0; i < count; ++i)
                valStack[allocaInst].pop();
        }
    };

    // 安全的入口调用
    if (!function.blocks.empty())
    {
        // 优先尝试 ID 为 0 的块，如果不存在则取第一个
        auto entryIt = cfg->id2block.find(0);
        if (entryIt != cfg->id2block.end())
            renameBlock(entryIt->second);
        else
            renameBlock(function.blocks.begin()->second);
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