#include <middleend/pass/dce_pass.h>
#include <middleend/pass/analysis/analysis_manager.h>
namespace ME
{
    void DcePass::runOnModule(Module& module)
    {
        for (auto* function : module.functions)
        {
            runOnFunction(*function);
        }
    }   
    void DcePass::runOnFunction(Function& function)
    {

        DceInFunction(function);
    }
    bool DcePass::DceInFunction(Function& function)
    {
        bool changed = false;
        for (auto& [blockId, block] : function.blocks)
        {
            bool reachable = true;

            auto& insts = block->insts;
            for (auto it = insts.begin(); it != insts.end(); )
            {
                Instruction* inst = *it;

                if (!reachable)
                {
                    // terminator 之后的指令不可达
                    delete inst;
                    it = insts.erase(it);
                    changed = true;
                    continue;
                }

                if (inst->isTerminator())
                {
                    // 遇到 terminator，后面全部不可达
                    reachable = false;
                }

                ++it;
            }
        }
        if (changed)
        {
            Analysis::AM.invalidate(function);
        }
        return changed;
    }
}