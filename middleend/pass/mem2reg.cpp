#include <middleend/pass/mem2reg.h>
#include <unordered_map>
#include <unordered_set>
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

bool Mem2Reg::Mem2Reg_3(Function& function, Analysis::DomInfo &dominfo)
{
    
}