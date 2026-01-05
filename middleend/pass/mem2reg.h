#ifndef __MIDDLEEND_Mem2Reg_H__
#define __MIDDLEEND_Mem2Reg_H__

#include <interfaces/middleend/pass.h>
#include <middleend/module/ir_module.h>
#include <middleend/module/ir_function.h>
#include <middleend/module/ir_block.h>
#include <middleend/module/ir_instruction.h>
#include <middleend/pass/analysis/cfg.h>
#include <middleend/pass/analysis/dominfo.h>
#include <middleend/visitor/utils/rename_visitor.h>
#include <interfaces/middleend/ir_visitor.h>
#include <vector>

namespace ME
{
    class Mem2Reg : public ModulePass
    {
      public:
        Mem2Reg()  = default;
        ~Mem2Reg() = default;

        void runOnModule(Module& module) override;
        void runOnFunction(Function& function) override;

      private:
        bool Mem2Reg_1(Function& function); // 删除未load的alloca指令
        bool Mem2Reg_2(Function& function); // def-use在同一block内的mem2reg
        bool Mem2Reg_3(Function& function); // 完整的mem2reg算法
    };

}  // namespace ME

#endif  // __MIDDLEEND_PASS_MEM2REG_H__