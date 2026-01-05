Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/licm_mem//test.ll
Step: -check
Output: standard output
Optimize level: 0

cse:
    domtree_cse:
        Function: main, Block: Block3
            -> %reg_19 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block3
            -> %reg_21 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block6
            -> %reg_40 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: main, Block: Block3
            -> %reg_21 = add 是 %reg_19 的公共子表达式

licm:
    invariant_load:
        Function: main, Block: Block5
            -> %reg_26 = 从全局变量 @g 的 load 可以被提升
    scalar_invariant:
        Function: main, Block: Block2
            -> %reg_8 = 标量指令是循环不变的但未被提升

sccp:
    constant_operand:
        Function: main, Block: Block1
            -> 操作数 %1 可以替换为常量（i32 0）
        Function: main, Block: Block2
            -> 操作数 %6 可以替换为常量（i32 63）
        Function: main, Block: Block2
            -> 操作数 %7 可以替换为常量（i32 1）
        Function: main, Block: Block3
            -> 操作数 %9 可以替换为常量（i32 10）
        Function: main, Block: Block4
            -> 操作数 %13 可以替换为常量（i32 0）
        Function: main, Block: Block4
            -> 操作数 %12 可以替换为常量（i32 514）
        Function: main, Block: Block4
            -> 操作数 %11 可以替换为常量（i32 114）
        Function: main, Block: Block4
            -> 操作数 %14 可以替换为常量（i32 0）
        Function: main, Block: Block5
            -> 操作数 %28 可以替换为常量（i32 1）
        Function: main, Block: Block6
            -> 操作数 %29 可以替换为常量（i32 0）
    foldable_instruction:
        Function: main, Block: Block0
            -> %reg_4 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block2
            -> %reg_8 = 指令结果为常量（i32 63）但未被折叠
        Function: main, Block: Block2
            -> %reg_10 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block3
            -> %reg_13 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block3
            -> %reg_17 = 指令结果为常量（i32 114）但未被折叠
        Function: main, Block: Block3
            -> %reg_18 = 指令结果为常量（i32 514）但未被折叠
        Function: main, Block: Block3
            -> %reg_19 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block3
            -> %reg_21 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block5
            -> %reg_37 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block6
            -> %reg_40 = 指令结果为常量（i32 0）但未被折叠
