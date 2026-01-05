#ifndef __BACKEND_TARGETS_RISCV64_RV64_REG_INFO_H__
#define __BACKEND_TARGETS_RISCV64_RV64_REG_INFO_H__

#include <backend/target/target_reg_info.h>
#include <backend/targets/riscv64/rv64_defs.h>
#include <map>

namespace BE::Targeting::RV64
{
    class RegInfo : public TargetRegInfo
    {
      public:
       RegInfo() 
        {
            // 初始化整数寄存器列表 x0-x31
            for (int i = 0; i <= 31; ++i) intRegs_.push_back(i);

            // 初始化浮点寄存器 f0-f31
            for (int i = 0; i <= 31; ++i) floatRegs_.push_back(i);

            // 保留寄存器: zero, ra, sp, gp, tp
            reservedRegs_ = {0, 1, 2, 3, 4};

            // callee-saved integer registers (s0-s11 = x8-x9, x18-x27)
            calleeSavedIntRegs_ = {8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

            // callee-saved float registers (f8-f9, f18-f27)
            calleeSavedFloatRegs_ = {8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

            // argument registers
            intArgRegs_   = {10, 11, 12, 13, 14, 15, 16, 17}; // a0-a7
            floatArgRegs_ = {10, 11, 12, 13, 14, 15, 16, 17}; // fa0-fa7
        }

        // 栈指针、返回地址、零寄存器
        int spRegId() const override { return 2; }    // x2 = sp
        int raRegId() const override { return 1; }    // x1 = ra
        int zeroRegId() const override { return 0; }  // x0 = zero

        // 参数寄存器
        const std::vector<int>& intArgRegs() const override { return intArgRegs_; }
        const std::vector<int>& floatArgRegs() const override { return floatArgRegs_; }

        // callee-saved
        const std::vector<int>& calleeSavedIntRegs() const override { return calleeSavedIntRegs_; }
        const std::vector<int>& calleeSavedFloatRegs() const override { return calleeSavedFloatRegs_; }

        // 所有寄存器、保留寄存器
        const std::vector<int>& reservedRegs() const override { return reservedRegs_; }
        const std::vector<int>& intRegs() const override { return intRegs_; }
        const std::vector<int>& floatRegs() const override { return floatRegs_; }

      private:
        std::vector<int> intRegs_;
        std::vector<int> floatRegs_;
        std::vector<int> reservedRegs_;
        std::vector<int> intArgRegs_;
        std::vector<int> floatArgRegs_;
        std::vector<int> calleeSavedIntRegs_;
        std::vector<int> calleeSavedFloatRegs_;
    };
}  // namespace BE::Targeting::RV64

#endif  // __BACKEND_TARGETS_RISCV64_RV64_REG_INFO_H__
