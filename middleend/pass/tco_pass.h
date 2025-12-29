#ifndef __MIDDLEEND_PASS_TCO_H__
#define __MIDDLEEND_PASS_TCO_H__

#include <interfaces/middleend/pass.h>
#include <middleend/module/ir_module.h>
#include <middleend/module/ir_function.h>
#include <middleend/module/ir_block.h>
#include <middleend/module/ir_instruction.h>
#include <middleend/pass/analysis/cfg.h>
#include <vector>

namespace ME
{
    class TcoPass : public ModulePass
    {
      public:
        TcoPass()  = default;
        ~TcoPass() = default;

        void runOnModule(Module& module) override;
        void runOnFunction(Function& function) override;

      private:
        bool TcoInFunction(Function& function);
    };

}  // namespace ME

#endif  // __MIDDLEEND_PASS_TCO_H__