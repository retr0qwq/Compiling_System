Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/lsr//test.ll
Step: -check
Output: standard output
Optimize level: 0

adce:
    dead_instruction:
        Function: main, Block: Block5
            -> 定义 %reg_38 的指令无用
        Function: main, Block: Block5
            -> 定义 %reg_34 的指令无用

cse:
    domtree_cse:
        Function: main, Block: Block6
            -> %reg_18 = add 是 %reg_2 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block5
            -> %reg_31 = add 是 %reg_2 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: main, Block: Block0
            -> %reg_4 = add 是 %reg_2 的公共子表达式

licm:
    scalar_invariant:
        Function: main, Block: Block1
            -> %reg_7 = 标量指令是循环不变的但未被提升

lsr:
    mul_strength_reduce:
        Function: main, Block: Block7
            -> %reg_23 = 4 * {%reg_13, +, -1} 可以通过强度削减变为辅助归纳变量 {4*%reg_13, +, 4*-1}

sccp:
    constant_operand:
        Function: main, Block: Block1
            -> 操作数 %0 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %5 可以替换为常量（i32 1024）
        Function: main, Block: Block2
            -> 操作数 %7 可以替换为常量（i32 1）
        Function: main, Block: Block3
            -> 操作数 %9 可以替换为常量（i32 511）
        Function: main, Block: Block5
            -> 操作数 %1 可以替换为常量（i32 0）
        Function: main, Block: Block5
            -> 操作数 %17 可以替换为常量（i32 0）
        Function: main, Block: Block6
            -> 操作数 %1 可以替换为常量（i32 0）
        Function: main, Block: Block6
            -> 操作数 %20 可以替换为常量（i32 0）
        Function: main, Block: Block7
            -> 操作数 %22 可以替换为常量（i32 4）
        Function: main, Block: Block7
            -> 操作数 %25 可以替换为常量（i32 1）
    foldable_instruction:
        Function: main, Block: Block0
            -> %reg_2 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_4 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block1
            -> %reg_7 = 指令结果为常量（i32 1024）但未被折叠
        Function: main, Block: Block2
            -> %reg_11 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block3
            -> %reg_15 = 指令结果为常量（i32 511）但未被折叠
        Function: main, Block: Block5
            -> %reg_31 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block6
            -> %reg_18 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block7
            -> %reg_21 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block7
            -> %reg_28 = 指令结果为常量（i32 1）但未被折叠
