Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/licm_scalar//test.ll
Step: -check
Output: standard output
Optimize level: 0

cse:
    domtree_cse:
        Function: main, Block: Block2
            -> %reg_186 = add 是 %reg_72 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block3
            -> %reg_201 = add 是 %reg_72 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: main, Block: Block0
            -> %reg_74 = add 是 %reg_72 的公共子表达式

licm:
    scalar_invariant:
        Function: main, Block: Block2
            -> %reg_132 = 标量指令是循环不变的但未被提升

sccp:
    constant_operand:
        Function: main, Block: Block1
            -> 操作数 %35 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %36 可以替换为常量（i32 0）
        Function: main, Block: Block2
            -> 操作数 %108 可以替换为常量（i32 2）
        Function: main, Block: Block2
            -> 操作数 %118 可以替换为常量（i32 324）
        Function: main, Block: Block2
            -> 操作数 %121 可以替换为常量（i32 4）
        Function: main, Block: Block2
            -> 操作数 %124 可以替换为常量（i32 22）
        Function: main, Block: Block2
            -> 操作数 %127 可以替换为常量（i32 5）
        Function: main, Block: Block2
            -> 操作数 %130 可以替换为常量（i32 3）
        Function: main, Block: Block2
            -> 操作数 %137 可以替换为常量（i32 100）
        Function: main, Block: Block2
            -> 操作数 %142 可以替换为常量（i32 0）
        Function: main, Block: Block3
            -> 操作数 %144 可以替换为常量（i32 10）
        Function: main, Block: Block3
            -> 操作数 %145 可以替换为常量（i32 0）
        Function: main, Block: Block5
            -> 操作数 %149 可以替换为常量（i32 998244353）
        Function: main, Block: Block5
            -> 操作数 %150 可以替换为常量（i32 1）
    foldable_instruction:
        Function: main, Block: Block0
            -> %reg_72 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_74 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block2
            -> %reg_132 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block2
            -> %reg_151 = 指令结果为常量（i32 324）但未被折叠
        Function: main, Block: Block2
            -> %reg_155 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block2
            -> %reg_159 = 指令结果为常量（i32 22）但未被折叠
        Function: main, Block: Block2
            -> %reg_163 = 指令结果为常量（i32 5）但未被折叠
        Function: main, Block: Block2
            -> %reg_167 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block2
            -> %reg_179 = 指令结果为常量（i32 100）但未被折叠
        Function: main, Block: Block2
            -> %reg_186 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block3
            -> %reg_200 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block3
            -> %reg_201 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block5
            -> %reg_194 = 指令结果为常量（i32 998244353）但未被折叠
        Function: main, Block: Block5
            -> %reg_197 = 指令结果为常量（i32 1）但未被折叠
