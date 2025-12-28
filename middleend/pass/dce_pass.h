#ifndef __MIDDLEEND_PASS_DCE_H__
#define __MIDDLEEND_PASS_DCE_H__

#include <interfaces/middleend/pass.h>
#include <middleend/module/ir_module.h>
#include <middleend/module/ir_function.h>
#include <middleend/module/ir_block.h>
#include <middleend/module/ir_instruction.h>
#include <middleend/pass/analysis/cfg.h>
#include <vector>

namespace ME
{
    class DcePass : public ModulePass
    {
      public:
        DcePass()  = default;
        ~DcePass() = default;

        void runOnModule(Module& module) override;
        void runOnFunction(Function& function) override;

      private:
        bool DceInFunction(Function& function);
    };

}  // namespace ME

#endif  // __MIDDLEEND_PASS_DCE_H__
