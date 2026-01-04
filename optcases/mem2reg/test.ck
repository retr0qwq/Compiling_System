Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/mem2reg//test.ll
Step: -check
Output: standard output
Optimize level: 0

adce:
    dead_instruction:
        Function: main, Block: Block0
            -> 定义 %reg_8 的指令无用

cse:
    domtree_cse:
        Function: main, Block: Block2
            -> %reg_26 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block2
            -> %reg_28 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block6
            -> %reg_32 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block9
            -> %reg_40 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block12
            -> %reg_48 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block15
            -> %reg_56 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block18
            -> %reg_64 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block21
            -> %reg_72 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block24
            -> %reg_81 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block25
            -> %reg_89 = add 是 %reg_50 的公共子表达式（定义在支配块 Block12 中）
        Function: main, Block: Block27
            -> %reg_92 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block28
            -> %reg_100 = add 是 %reg_58 的公共子表达式（定义在支配块 Block15 中）
        Function: main, Block: Block30
            -> %reg_103 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block31
            -> %reg_108 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block3
            -> %reg_117 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block3
            -> %reg_119 = add 是 %reg_10 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block3
            -> %reg_120 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: main, Block: Block0
            -> %reg_6 = add 是 %reg_4 的公共子表达式
        Function: main, Block: Block0
            -> %reg_8 = add 是 %reg_4 的公共子表达式
        Function: main, Block: Block0
            -> %reg_12 = add 是 %reg_10 的公共子表达式
        Function: main, Block: Block3
            -> %reg_119 = add 是 %reg_117 的公共子表达式

licm:
    scalar_invariant:
        Function: main, Block: Block2
            -> %reg_26 = 标量指令是循环不变的但未被提升

sccp:
    constant_operand:
        Function: main, Block: Block0
            -> 操作数 %4 可以替换为常量（i32 10）
        Function: main, Block: Block0
            -> 操作数 %5 可以替换为常量（i32 10）
        Function: main, Block: Block0
            -> 操作数 %4 可以替换为常量（i32 10）
        Function: main, Block: Block0
            -> 操作数 %6 可以替换为常量（i32 0）
        Function: main, Block: Block0
            -> 操作数 %5 可以替换为常量（i32 10）
        Function: main, Block: Block0
            -> 操作数 %7 可以替换为常量（i32 10）
        Function: main, Block: Block1
            -> 操作数 %0 可以替换为常量（i32 1000000）
        Function: main, Block: Block1
            -> 操作数 %9 可以替换为常量（i32 1000000）
        Function: main, Block: Block1
            -> 操作数 %1 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %2 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %8 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %9 可以替换为常量（i32 1000000）
        Function: main, Block: Block2
            -> 操作数 %17 可以替换为常量（i32 10）
        Function: main, Block: Block2
            -> 操作数 %19 可以替换为常量（i32 0）
        Function: main, Block: Block3
            -> 操作数 %21 可以替换为常量（i32 10）
        Function: main, Block: Block3
            -> 操作数 %22 可以替换为常量（i32 10）
        Function: main, Block: Block3
            -> 操作数 %23 可以替换为常量（i32 0）
        Function: main, Block: Block5
            -> 操作数 %28 可以替换为常量（i32 1）
        Function: main, Block: Block6
            -> 操作数 %29 可以替换为常量（i32 10）
        Function: main, Block: Block6
            -> 操作数 %31 可以替换为常量（i32 1）
        Function: main, Block: Block7
            -> 操作数 %33 可以替换为常量（i32 2）
        Function: main, Block: Block9
            -> 操作数 %38 可以替换为常量（i32 10）
        Function: main, Block: Block9
            -> 操作数 %40 可以替换为常量（i32 2）
        Function: main, Block: Block10
            -> 操作数 %42 可以替换为常量（i32 3）
        Function: main, Block: Block12
            -> 操作数 %47 可以替换为常量（i32 10）
        Function: main, Block: Block12
            -> 操作数 %49 可以替换为常量（i32 3）
        Function: main, Block: Block13
            -> 操作数 %51 可以替换为常量（i32 4）
        Function: main, Block: Block15
            -> 操作数 %56 可以替换为常量（i32 10）
        Function: main, Block: Block15
            -> 操作数 %58 可以替换为常量（i32 4）
        Function: main, Block: Block16
            -> 操作数 %60 可以替换为常量（i32 5）
        Function: main, Block: Block18
            -> 操作数 %65 可以替换为常量（i32 10）
        Function: main, Block: Block18
            -> 操作数 %67 可以替换为常量（i32 5）
        Function: main, Block: Block19
            -> 操作数 %69 可以替换为常量（i32 6）
        Function: main, Block: Block21
            -> 操作数 %74 可以替换为常量（i32 10）
        Function: main, Block: Block21
            -> 操作数 %76 可以替换为常量（i32 6）
        Function: main, Block: Block22
            -> 操作数 %78 可以替换为常量（i32 7）
        Function: main, Block: Block24
            -> 操作数 %83 可以替换为常量（i32 10）
        Function: main, Block: Block24
            -> 操作数 %85 可以替换为常量（i32 7）
        Function: main, Block: Block25
            -> 操作数 %87 可以替换为常量（i32 8）
        Function: main, Block: Block25
            -> 操作数 %89 可以替换为常量（i32 3）
        Function: main, Block: Block27
            -> 操作数 %94 可以替换为常量（i32 10）
        Function: main, Block: Block27
            -> 操作数 %96 可以替换为常量（i32 8）
        Function: main, Block: Block28
            -> 操作数 %98 可以替换为常量（i32 9）
        Function: main, Block: Block28
            -> 操作数 %100 可以替换为常量（i32 4）
        Function: main, Block: Block30
            -> 操作数 %104 可以替换为常量（i32 10）
        Function: main, Block: Block30
            -> 操作数 %106 可以替换为常量（i32 9）
        Function: main, Block: Block31
            -> 操作数 %108 可以替换为常量（i32 10）
        Function: main, Block: Block31
            -> 操作数 %110 可以替换为常量（i32 11）
    foldable_instruction:
        Function: main, Block: Block0
            -> %reg_2 = 指令结果为常量（i32 1000000）但未被折叠
        Function: main, Block: Block0
            -> %reg_4 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_6 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_8 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_10 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block0
            -> %reg_12 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block0
            -> %reg_16 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_19 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block0
            -> %reg_21 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block1
            -> %reg_153 = 指令结果为常量（i32 1000000）但未被折叠
        Function: main, Block: Block2
            -> %reg_26 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block2
            -> %reg_28 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block3
            -> %reg_117 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block3
            -> %reg_119 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block3
            -> %reg_120 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block5
            -> %reg_114 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block6
            -> %reg_32 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block6
            -> %reg_34 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block7
            -> %reg_37 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block9
            -> %reg_40 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block9
            -> %reg_42 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block10
            -> %reg_45 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block12
            -> %reg_48 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block12
            -> %reg_50 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block13
            -> %reg_53 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block15
            -> %reg_56 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block15
            -> %reg_58 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block16
            -> %reg_61 = 指令结果为常量（i32 5）但未被折叠
        Function: main, Block: Block18
            -> %reg_64 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block18
            -> %reg_66 = 指令结果为常量（i32 5）但未被折叠
        Function: main, Block: Block19
            -> %reg_69 = 指令结果为常量（i32 6）但未被折叠
        Function: main, Block: Block21
            -> %reg_72 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block21
            -> %reg_74 = 指令结果为常量（i32 6）但未被折叠
        Function: main, Block: Block22
            -> %reg_77 = 指令结果为常量（i32 7）但未被折叠
        Function: main, Block: Block24
            -> %reg_81 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block24
            -> %reg_83 = 指令结果为常量（i32 7）但未被折叠
        Function: main, Block: Block25
            -> %reg_86 = 指令结果为常量（i32 8）但未被折叠
        Function: main, Block: Block25
            -> %reg_89 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block27
            -> %reg_92 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block27
            -> %reg_94 = 指令结果为常量（i32 8）但未被折叠
        Function: main, Block: Block28
            -> %reg_97 = 指令结果为常量（i32 9）但未被折叠
        Function: main, Block: Block28
            -> %reg_100 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block30
            -> %reg_103 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block30
            -> %reg_105 = 指令结果为常量（i32 9）但未被折叠
        Function: main, Block: Block31
            -> %reg_108 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block31
            -> %reg_111 = 指令结果为常量（i32 11）但未被折叠
