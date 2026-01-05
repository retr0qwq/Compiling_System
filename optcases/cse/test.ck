Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/cse//test.ll
Step: -check
Output: standard output
Optimize level: 0

adce:
    dead_instruction:
        Function: func, Block: Block1
            -> 定义 %reg_3402 的指令无用
        Function: main, Block: Block1
            -> 定义 %reg_93 的指令无用
        Function: main, Block: Block1
            -> 定义 %reg_92 的指令无用
        Function: main, Block: Block1
            -> 定义 %reg_91 的指令无用
        Function: main, Block: Block1
            -> 定义 %reg_90 的指令无用

cse:
    domtree_cse:
        Function: func, Block: Block2
            -> %reg_39 = add 是 %reg_32 的公共子表达式（定义在支配块 Block0 中）
        Function: func, Block: Block2
            -> %reg_318 = add 是 %reg_32 的公共子表达式（定义在支配块 Block0 中）
        Function: func, Block: Block4
            -> %reg_321 = add 是 %reg_32 的公共子表达式（定义在支配块 Block0 中）
        Function: func, Block: Block32
            -> %reg_3387 = add 是 %reg_32 的公共子表达式（定义在支配块 Block0 中）
        Function: func, Block: Block6
            -> %reg_325 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block7
            -> %reg_355 = add 是 %reg_352 的公共子表达式（定义在支配块 Block6 中）
        Function: func, Block: Block9
            -> %reg_359 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block10
            -> %reg_389 = add 是 %reg_386 的公共子表达式（定义在支配块 Block9 中）
        Function: func, Block: Block12
            -> %reg_393 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block13
            -> %reg_423 = add 是 %reg_420 的公共子表达式（定义在支配块 Block12 中）
        Function: func, Block: Block15
            -> %reg_427 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block16
            -> %reg_457 = add 是 %reg_454 的公共子表达式（定义在支配块 Block15 中）
        Function: func, Block: Block18
            -> %reg_461 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block19
            -> %reg_491 = add 是 %reg_488 的公共子表达式（定义在支配块 Block18 中）
        Function: func, Block: Block21
            -> %reg_495 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block22
            -> %reg_525 = add 是 %reg_522 的公共子表达式（定义在支配块 Block21 中）
        Function: func, Block: Block24
            -> %reg_529 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block25
            -> %reg_559 = add 是 %reg_556 的公共子表达式（定义在支配块 Block24 中）
        Function: func, Block: Block27
            -> %reg_563 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式（定义在支配块 Block2 中）
        Function: func, Block: Block28
            -> %reg_593 = add 是 %reg_590 的公共子表达式（定义在支配块 Block27 中）
        Function: main, Block: Block3
            -> %reg_84 = add 是 %reg_9 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block4
            -> %reg_87 = add 是 %reg_9 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block5
            -> %reg_89 = add 是 %reg_13 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: func, Block: Block0
            -> %reg_34 = add 是 %reg_32 的公共子表达式
        Function: func, Block: Block2
            -> %reg_74 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_105 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_136 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_167 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_198 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_229 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_260 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_291 = add(%reg_3450, %reg_3432) 是 %reg_43 的公共子表达式
        Function: func, Block: Block2
            -> %reg_318 = add 是 %reg_39 的公共子表达式
        Function: func, Block: Block5
            -> %reg_628 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_659 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_690 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_721 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_752 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_783 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_814 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_845 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_876 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_907 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_938 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_969 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1000 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1031 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1062 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1093 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1124 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1155 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1186 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1217 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1248 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1279 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1310 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1341 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1372 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1403 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1434 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1465 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1496 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1527 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1558 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1589 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1620 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1651 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1682 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1713 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1744 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1775 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1806 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1837 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1868 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1899 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1930 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1961 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_1992 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2023 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2054 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2085 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2116 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2147 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2178 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2209 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2240 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2271 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2302 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2333 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2364 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2395 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2426 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2457 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2488 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2519 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2550 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2581 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2612 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2643 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2674 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2705 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2736 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2767 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2798 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2829 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2860 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2891 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2922 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2953 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_2984 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3015 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3046 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3077 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3108 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3139 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3170 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3201 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3232 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3263 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3294 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3325 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: func, Block: Block5
            -> %reg_3355 = add(%reg_3451, %reg_3433) 是 %reg_597 的公共子表达式
        Function: main, Block: Block3
            -> %reg_60 = add(%reg_100, %reg_99) 是 %reg_51 的公共子表达式
        Function: main, Block: Block3
            -> %reg_74 = add 是 %reg_71 的公共子表达式
        Function: main, Block: Block3
            -> %reg_79 = add 是 %reg_67 的公共子表达式

licm:
    invariant_load:
        Function: func, Block: Block1
            -> %reg_36 = 从全局变量 @loopCount 的 load 可以被提升
    scalar_invariant:
        Function: func, Block: Block2
            -> %reg_39 = 标量指令是循环不变的但未被提升

sccp:
    constant_operand:
        Function: func, Block: Block1
            -> 操作数 %15 可以替换为常量（i32 0）
        Function: func, Block: Block1
            -> 操作数 %16 可以替换为常量（i32 0）
        Function: func, Block: Block2
            -> 操作数 %55 可以替换为常量（i32 0）
        Function: func, Block: Block2
            -> 操作数 %190 可以替换为常量（i32 0）
        Function: func, Block: Block5
            -> 操作数 %193 可以替换为常量（i32 0）
        Function: func, Block: Block6
            -> 操作数 %1575 可以替换为常量（i32 1）
        Function: func, Block: Block8
            -> 操作数 %1578 可以替换为常量（i32 1）
        Function: func, Block: Block9
            -> 操作数 %1609 可以替换为常量（i32 2）
        Function: func, Block: Block11
            -> 操作数 %1612 可以替换为常量（i32 2）
        Function: func, Block: Block12
            -> 操作数 %1643 可以替换为常量（i32 3）
        Function: func, Block: Block14
            -> 操作数 %1646 可以替换为常量（i32 3）
        Function: func, Block: Block15
            -> 操作数 %1677 可以替换为常量（i32 4）
        Function: func, Block: Block17
            -> 操作数 %1680 可以替换为常量（i32 4）
        Function: func, Block: Block18
            -> 操作数 %1711 可以替换为常量（i32 5）
        Function: func, Block: Block20
            -> 操作数 %1714 可以替换为常量（i32 5）
        Function: func, Block: Block21
            -> 操作数 %1745 可以替换为常量（i32 6）
        Function: func, Block: Block23
            -> 操作数 %1748 可以替换为常量（i32 6）
        Function: func, Block: Block24
            -> 操作数 %1779 可以替换为常量（i32 7）
        Function: func, Block: Block26
            -> 操作数 %1782 可以替换为常量（i32 7）
        Function: func, Block: Block27
            -> 操作数 %1798 可以替换为常量（i32 8）
        Function: func, Block: Block29
            -> 操作数 %1801 可以替换为常量（i32 8）
        Function: func, Block: Block30
            -> 操作数 %1802 可以替换为常量（i32 1）
        Function: func, Block: Block31
            -> 操作数 %1806 可以替换为常量（i32 100）
        Function: func, Block: Block31
            -> 操作数 %1808 可以替换为常量（i32 1500000001）
        Function: func, Block: Block31
            -> 操作数 %1809 可以替换为常量（i32 1）
        Function: func, Block: Block32
            -> 操作数 %1810 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %4 可以替换为常量（i32 10）
        Function: main, Block: Block1
            -> 操作数 %6 可以替换为常量（i32 0）
        Function: main, Block: Block2
            -> 操作数 %24 可以替换为常量（i32 3）
        Function: main, Block: Block2
            -> 操作数 %27 可以替换为常量（i32 2）
        Function: main, Block: Block2
            -> 操作数 %29 可以替换为常量（i32 1）
        Function: main, Block: Block3
            -> 操作数 %35 可以替换为常量（i32 2）
        Function: main, Block: Block3
            -> 操作数 %37 可以替换为常量（i32 3）
        Function: main, Block: Block3
            -> 操作数 %39 可以替换为常量（i32 3）
        Function: main, Block: Block3
            -> 操作数 %42 可以替换为常量（i32 2）
        Function: main, Block: Block3
            -> 操作数 %45 可以替换为常量（i32 10）
        Function: main, Block: Block4
            -> 操作数 %47 可以替换为常量（i32 63）
        Function: main, Block: Block5
            -> 操作数 %48 可以替换为常量（i32 10）
        Function: main, Block: Block5
            -> 操作数 %50 可以替换为常量（i32 0）
    foldable_instruction:
        Function: func, Block: Block0
            -> %reg_32 = 指令结果为常量（i32 0）但未被折叠
        Function: func, Block: Block0
            -> %reg_34 = 指令结果为常量（i32 0）但未被折叠
        Function: func, Block: Block2
            -> %reg_39 = 指令结果为常量（i32 0）但未被折叠
        Function: func, Block: Block2
            -> %reg_318 = 指令结果为常量（i32 0）但未被折叠
        Function: func, Block: Block4
            -> %reg_321 = 指令结果为常量（i32 0）但未被折叠
        Function: func, Block: Block6
            -> %reg_352 = 指令结果为常量（i32 1）但未被折叠
        Function: func, Block: Block7
            -> %reg_355 = 指令结果为常量（i32 1）但未被折叠
        Function: func, Block: Block9
            -> %reg_386 = 指令结果为常量（i32 2）但未被折叠
        Function: func, Block: Block10
            -> %reg_389 = 指令结果为常量（i32 2）但未被折叠
        Function: func, Block: Block12
            -> %reg_420 = 指令结果为常量（i32 3）但未被折叠
        Function: func, Block: Block13
            -> %reg_423 = 指令结果为常量（i32 3）但未被折叠
        Function: func, Block: Block15
            -> %reg_454 = 指令结果为常量（i32 4）但未被折叠
        Function: func, Block: Block16
            -> %reg_457 = 指令结果为常量（i32 4）但未被折叠
        Function: func, Block: Block18
            -> %reg_488 = 指令结果为常量（i32 5）但未被折叠
        Function: func, Block: Block19
            -> %reg_491 = 指令结果为常量（i32 5）但未被折叠
        Function: func, Block: Block21
            -> %reg_522 = 指令结果为常量（i32 6）但未被折叠
        Function: func, Block: Block22
            -> %reg_525 = 指令结果为常量（i32 6）但未被折叠
        Function: func, Block: Block24
            -> %reg_556 = 指令结果为常量（i32 7）但未被折叠
        Function: func, Block: Block25
            -> %reg_559 = 指令结果为常量（i32 7）但未被折叠
        Function: func, Block: Block27
            -> %reg_590 = 指令结果为常量（i32 8）但未被折叠
        Function: func, Block: Block28
            -> %reg_593 = 指令结果为常量（i32 8）但未被折叠
        Function: func, Block: Block30
            -> %reg_3384 = 指令结果为常量（i32 1）但未被折叠
        Function: func, Block: Block31
            -> %reg_3390 = 指令结果为常量（i32 100）但未被折叠
        Function: func, Block: Block31
            -> %reg_3396 = 指令结果为常量（i32 1500000001）但未被折叠
        Function: func, Block: Block31
            -> %reg_3399 = 指令结果为常量（i32 1）但未被折叠
        Function: func, Block: Block32
            -> %reg_3387 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_9 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block0
            -> %reg_13 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block2
            -> %reg_27 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block2
            -> %reg_31 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block2
            -> %reg_43 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block3
            -> %reg_67 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block3
            -> %reg_71 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block3
            -> %reg_74 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block3
            -> %reg_79 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block3
            -> %reg_84 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block4
            -> %reg_86 = 指令结果为常量（i32 63）但未被折叠
        Function: main, Block: Block4
            -> %reg_87 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block5
            -> %reg_89 = 指令结果为常量（i32 0）但未被折叠
