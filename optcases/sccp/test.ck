Input file: /mnt/c/Users/76524/Desktop/课程/大四上/编译/NKU-Compiler2025/optcases/sccp//test.ll
Step: -check
Output: standard output
Optimize level: 0

adce:
    dead_instruction:
        Function: main, Block: Block4
            -> 定义 %reg_640 的指令无用

cse:
    domtree_cse:
        Function: main, Block: Block2
            -> %reg_15 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block7
            -> %reg_25 = add 是 %reg_23 的公共子表达式（定义在支配块 Block5 中）
        Function: main, Block: Block9
            -> %reg_29 = add 是 %reg_27 的公共子表达式（定义在支配块 Block7 中）
        Function: main, Block: Block11
            -> %reg_33 = add 是 %reg_31 的公共子表达式（定义在支配块 Block9 中）
        Function: main, Block: Block13
            -> %reg_37 = add 是 %reg_35 的公共子表达式（定义在支配块 Block11 中）
        Function: main, Block: Block15
            -> %reg_41 = add 是 %reg_39 的公共子表达式（定义在支配块 Block13 中）
        Function: main, Block: Block17
            -> %reg_45 = add 是 %reg_43 的公共子表达式（定义在支配块 Block15 中）
        Function: main, Block: Block19
            -> %reg_49 = add 是 %reg_47 的公共子表达式（定义在支配块 Block17 中）
        Function: main, Block: Block21
            -> %reg_53 = add 是 %reg_51 的公共子表达式（定义在支配块 Block19 中）
        Function: main, Block: Block23
            -> %reg_57 = add 是 %reg_55 的公共子表达式（定义在支配块 Block21 中）
        Function: main, Block: Block25
            -> %reg_61 = add 是 %reg_59 的公共子表达式（定义在支配块 Block23 中）
        Function: main, Block: Block27
            -> %reg_65 = add 是 %reg_63 的公共子表达式（定义在支配块 Block25 中）
        Function: main, Block: Block29
            -> %reg_69 = add 是 %reg_67 的公共子表达式（定义在支配块 Block27 中）
        Function: main, Block: Block31
            -> %reg_73 = add 是 %reg_71 的公共子表达式（定义在支配块 Block29 中）
        Function: main, Block: Block33
            -> %reg_77 = add 是 %reg_75 的公共子表达式（定义在支配块 Block31 中）
        Function: main, Block: Block35
            -> %reg_81 = add 是 %reg_79 的公共子表达式（定义在支配块 Block33 中）
        Function: main, Block: Block37
            -> %reg_85 = add 是 %reg_83 的公共子表达式（定义在支配块 Block35 中）
        Function: main, Block: Block39
            -> %reg_89 = add 是 %reg_87 的公共子表达式（定义在支配块 Block37 中）
        Function: main, Block: Block41
            -> %reg_93 = add 是 %reg_91 的公共子表达式（定义在支配块 Block39 中）
        Function: main, Block: Block43
            -> %reg_97 = add 是 %reg_95 的公共子表达式（定义在支配块 Block41 中）
        Function: main, Block: Block45
            -> %reg_101 = add 是 %reg_99 的公共子表达式（定义在支配块 Block43 中）
        Function: main, Block: Block47
            -> %reg_105 = add 是 %reg_103 的公共子表达式（定义在支配块 Block45 中）
        Function: main, Block: Block49
            -> %reg_109 = add 是 %reg_107 的公共子表达式（定义在支配块 Block47 中）
        Function: main, Block: Block51
            -> %reg_113 = add 是 %reg_111 的公共子表达式（定义在支配块 Block49 中）
        Function: main, Block: Block53
            -> %reg_117 = add 是 %reg_115 的公共子表达式（定义在支配块 Block51 中）
        Function: main, Block: Block55
            -> %reg_121 = add 是 %reg_119 的公共子表达式（定义在支配块 Block53 中）
        Function: main, Block: Block57
            -> %reg_125 = add 是 %reg_123 的公共子表达式（定义在支配块 Block55 中）
        Function: main, Block: Block59
            -> %reg_129 = add 是 %reg_127 的公共子表达式（定义在支配块 Block57 中）
        Function: main, Block: Block61
            -> %reg_133 = add 是 %reg_131 的公共子表达式（定义在支配块 Block59 中）
        Function: main, Block: Block63
            -> %reg_137 = add 是 %reg_135 的公共子表达式（定义在支配块 Block61 中）
        Function: main, Block: Block65
            -> %reg_141 = add 是 %reg_139 的公共子表达式（定义在支配块 Block63 中）
        Function: main, Block: Block67
            -> %reg_145 = add 是 %reg_143 的公共子表达式（定义在支配块 Block65 中）
        Function: main, Block: Block69
            -> %reg_149 = add 是 %reg_147 的公共子表达式（定义在支配块 Block67 中）
        Function: main, Block: Block71
            -> %reg_153 = add 是 %reg_151 的公共子表达式（定义在支配块 Block69 中）
        Function: main, Block: Block73
            -> %reg_157 = add 是 %reg_155 的公共子表达式（定义在支配块 Block71 中）
        Function: main, Block: Block75
            -> %reg_161 = add 是 %reg_159 的公共子表达式（定义在支配块 Block73 中）
        Function: main, Block: Block77
            -> %reg_165 = add 是 %reg_163 的公共子表达式（定义在支配块 Block75 中）
        Function: main, Block: Block79
            -> %reg_169 = add 是 %reg_167 的公共子表达式（定义在支配块 Block77 中）
        Function: main, Block: Block81
            -> %reg_173 = add 是 %reg_171 的公共子表达式（定义在支配块 Block79 中）
        Function: main, Block: Block83
            -> %reg_177 = add 是 %reg_175 的公共子表达式（定义在支配块 Block81 中）
        Function: main, Block: Block85
            -> %reg_181 = add 是 %reg_179 的公共子表达式（定义在支配块 Block83 中）
        Function: main, Block: Block87
            -> %reg_185 = add 是 %reg_183 的公共子表达式（定义在支配块 Block85 中）
        Function: main, Block: Block89
            -> %reg_189 = add 是 %reg_187 的公共子表达式（定义在支配块 Block87 中）
        Function: main, Block: Block91
            -> %reg_193 = add 是 %reg_191 的公共子表达式（定义在支配块 Block89 中）
        Function: main, Block: Block93
            -> %reg_197 = add 是 %reg_195 的公共子表达式（定义在支配块 Block91 中）
        Function: main, Block: Block95
            -> %reg_201 = add 是 %reg_199 的公共子表达式（定义在支配块 Block93 中）
        Function: main, Block: Block97
            -> %reg_205 = add 是 %reg_203 的公共子表达式（定义在支配块 Block95 中）
        Function: main, Block: Block99
            -> %reg_209 = add 是 %reg_207 的公共子表达式（定义在支配块 Block97 中）
        Function: main, Block: Block101
            -> %reg_213 = add 是 %reg_211 的公共子表达式（定义在支配块 Block99 中）
        Function: main, Block: Block103
            -> %reg_217 = add 是 %reg_215 的公共子表达式（定义在支配块 Block101 中）
        Function: main, Block: Block105
            -> %reg_221 = add 是 %reg_219 的公共子表达式（定义在支配块 Block103 中）
        Function: main, Block: Block107
            -> %reg_225 = add 是 %reg_223 的公共子表达式（定义在支配块 Block105 中）
        Function: main, Block: Block109
            -> %reg_229 = add 是 %reg_227 的公共子表达式（定义在支配块 Block107 中）
        Function: main, Block: Block111
            -> %reg_233 = add 是 %reg_231 的公共子表达式（定义在支配块 Block109 中）
        Function: main, Block: Block113
            -> %reg_237 = add 是 %reg_235 的公共子表达式（定义在支配块 Block111 中）
        Function: main, Block: Block115
            -> %reg_241 = add 是 %reg_239 的公共子表达式（定义在支配块 Block113 中）
        Function: main, Block: Block117
            -> %reg_245 = add 是 %reg_243 的公共子表达式（定义在支配块 Block115 中）
        Function: main, Block: Block119
            -> %reg_249 = add 是 %reg_247 的公共子表达式（定义在支配块 Block117 中）
        Function: main, Block: Block121
            -> %reg_253 = add 是 %reg_251 的公共子表达式（定义在支配块 Block119 中）
        Function: main, Block: Block123
            -> %reg_257 = add 是 %reg_255 的公共子表达式（定义在支配块 Block121 中）
        Function: main, Block: Block125
            -> %reg_261 = add 是 %reg_259 的公共子表达式（定义在支配块 Block123 中）
        Function: main, Block: Block127
            -> %reg_265 = add 是 %reg_263 的公共子表达式（定义在支配块 Block125 中）
        Function: main, Block: Block129
            -> %reg_269 = add 是 %reg_267 的公共子表达式（定义在支配块 Block127 中）
        Function: main, Block: Block131
            -> %reg_273 = add 是 %reg_271 的公共子表达式（定义在支配块 Block129 中）
        Function: main, Block: Block133
            -> %reg_277 = add 是 %reg_275 的公共子表达式（定义在支配块 Block131 中）
        Function: main, Block: Block135
            -> %reg_281 = add 是 %reg_279 的公共子表达式（定义在支配块 Block133 中）
        Function: main, Block: Block137
            -> %reg_285 = add 是 %reg_283 的公共子表达式（定义在支配块 Block135 中）
        Function: main, Block: Block139
            -> %reg_289 = add 是 %reg_287 的公共子表达式（定义在支配块 Block137 中）
        Function: main, Block: Block141
            -> %reg_293 = add 是 %reg_291 的公共子表达式（定义在支配块 Block139 中）
        Function: main, Block: Block143
            -> %reg_297 = add 是 %reg_295 的公共子表达式（定义在支配块 Block141 中）
        Function: main, Block: Block145
            -> %reg_301 = add 是 %reg_299 的公共子表达式（定义在支配块 Block143 中）
        Function: main, Block: Block147
            -> %reg_305 = add 是 %reg_303 的公共子表达式（定义在支配块 Block145 中）
        Function: main, Block: Block149
            -> %reg_309 = add 是 %reg_307 的公共子表达式（定义在支配块 Block147 中）
        Function: main, Block: Block151
            -> %reg_313 = add 是 %reg_311 的公共子表达式（定义在支配块 Block149 中）
        Function: main, Block: Block153
            -> %reg_317 = add 是 %reg_315 的公共子表达式（定义在支配块 Block151 中）
        Function: main, Block: Block155
            -> %reg_321 = add 是 %reg_319 的公共子表达式（定义在支配块 Block153 中）
        Function: main, Block: Block157
            -> %reg_325 = add 是 %reg_323 的公共子表达式（定义在支配块 Block155 中）
        Function: main, Block: Block159
            -> %reg_329 = add 是 %reg_327 的公共子表达式（定义在支配块 Block157 中）
        Function: main, Block: Block161
            -> %reg_333 = add 是 %reg_331 的公共子表达式（定义在支配块 Block159 中）
        Function: main, Block: Block163
            -> %reg_337 = add 是 %reg_335 的公共子表达式（定义在支配块 Block161 中）
        Function: main, Block: Block165
            -> %reg_341 = add 是 %reg_339 的公共子表达式（定义在支配块 Block163 中）
        Function: main, Block: Block167
            -> %reg_345 = add 是 %reg_343 的公共子表达式（定义在支配块 Block165 中）
        Function: main, Block: Block169
            -> %reg_349 = add 是 %reg_347 的公共子表达式（定义在支配块 Block167 中）
        Function: main, Block: Block171
            -> %reg_353 = add 是 %reg_351 的公共子表达式（定义在支配块 Block169 中）
        Function: main, Block: Block173
            -> %reg_357 = add 是 %reg_355 的公共子表达式（定义在支配块 Block171 中）
        Function: main, Block: Block175
            -> %reg_361 = add 是 %reg_359 的公共子表达式（定义在支配块 Block173 中）
        Function: main, Block: Block177
            -> %reg_365 = add 是 %reg_363 的公共子表达式（定义在支配块 Block175 中）
        Function: main, Block: Block179
            -> %reg_369 = add 是 %reg_367 的公共子表达式（定义在支配块 Block177 中）
        Function: main, Block: Block181
            -> %reg_373 = add 是 %reg_371 的公共子表达式（定义在支配块 Block179 中）
        Function: main, Block: Block183
            -> %reg_377 = add 是 %reg_375 的公共子表达式（定义在支配块 Block181 中）
        Function: main, Block: Block185
            -> %reg_381 = add 是 %reg_379 的公共子表达式（定义在支配块 Block183 中）
        Function: main, Block: Block187
            -> %reg_385 = add 是 %reg_383 的公共子表达式（定义在支配块 Block185 中）
        Function: main, Block: Block189
            -> %reg_389 = add 是 %reg_387 的公共子表达式（定义在支配块 Block187 中）
        Function: main, Block: Block191
            -> %reg_393 = add 是 %reg_391 的公共子表达式（定义在支配块 Block189 中）
        Function: main, Block: Block193
            -> %reg_397 = add 是 %reg_395 的公共子表达式（定义在支配块 Block191 中）
        Function: main, Block: Block195
            -> %reg_401 = add 是 %reg_399 的公共子表达式（定义在支配块 Block193 中）
        Function: main, Block: Block197
            -> %reg_405 = add 是 %reg_403 的公共子表达式（定义在支配块 Block195 中）
        Function: main, Block: Block199
            -> %reg_409 = add 是 %reg_407 的公共子表达式（定义在支配块 Block197 中）
        Function: main, Block: Block201
            -> %reg_413 = add 是 %reg_411 的公共子表达式（定义在支配块 Block199 中）
        Function: main, Block: Block203
            -> %reg_417 = add 是 %reg_415 的公共子表达式（定义在支配块 Block201 中）
        Function: main, Block: Block8
            -> %reg_419 = add 是 %reg_23 的公共子表达式（定义在支配块 Block5 中）
        Function: main, Block: Block8
            -> %reg_422 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
        Function: main, Block: Block205
            -> %reg_424 = add 是 %reg_13 的公共子表达式（定义在支配块 Block1 中）
        Function: main, Block: Block206
            -> %reg_430 = add 是 %reg_23 的公共子表达式（定义在支配块 Block5 中）
        Function: main, Block: Block6
            -> %reg_437 = add 是 %reg_4 的公共子表达式（定义在支配块 Block0 中）
    local_cse:
        Function: main, Block: Block0
            -> %reg_8 = add 是 %reg_4 的公共子表达式
        Function: main, Block: Block0
            -> %reg_11 = add 是 %reg_4 的公共子表达式

licm:
    scalar_invariant:
        Function: main, Block: Block1
            -> %reg_13 = 标量指令是循环不变的但未被提升

sccp:
    constant_operand:
        Function: main, Block: Block1
            -> 操作数 %4 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %7 可以替换为常量（i32 0）
        Function: main, Block: Block1
            -> 操作数 %9 可以替换为常量（i32 100）
        Function: main, Block: Block2
            -> 操作数 %11 可以替换为常量（i32 1）
        Function: main, Block: Block4
            -> 操作数 %1 可以替换为常量（i32 0）
        Function: main, Block: Block4
            -> 操作数 %2 可以替换为常量（i32 200）
        Function: main, Block: Block4
            -> 操作数 %17 可以替换为常量（i32 200）
        Function: main, Block: Block4
            -> 操作数 %3 可以替换为常量（i32 0）
        Function: main, Block: Block4
            -> 操作数 %8 可以替换为常量（i32 0）
        Function: main, Block: Block4
            -> 操作数 %21 可以替换为常量（i32 99）
        Function: main, Block: Block5
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block5
            -> 操作数 %24 可以替换为常量（i32 1）
        Function: main, Block: Block5
            -> 操作数 %25 可以替换为常量（i32 1）
        Function: main, Block: Block6
            -> 操作数 %26 可以替换为常量（i32 10）
        Function: main, Block: Block6
            -> 操作数 %27 可以替换为常量（i32 0）
        Function: main, Block: Block7
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block7
            -> 操作数 %29 可以替换为常量（i32 2）
        Function: main, Block: Block7
            -> 操作数 %30 可以替换为常量（i32 1）
        Function: main, Block: Block8
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block8
            -> 操作数 %31 可以替换为常量（i32 200）
        Function: main, Block: Block8
            -> 操作数 %32 可以替换为常量（i32 99）
        Function: main, Block: Block8
            -> 操作数 %34 可以替换为常量（i32 1）
        Function: main, Block: Block9
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block9
            -> 操作数 %37 可以替换为常量（i32 3）
        Function: main, Block: Block9
            -> 操作数 %38 可以替换为常量（i32 1）
        Function: main, Block: Block10
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block10
            -> 操作数 %39 可以替换为常量（i32 200）
        Function: main, Block: Block10
            -> 操作数 %28 可以替换为常量（i32 1）
        Function: main, Block: Block10
            -> 操作数 %40 可以替换为常量（i32 99）
        Function: main, Block: Block11
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block11
            -> 操作数 %42 可以替换为常量（i32 4）
        Function: main, Block: Block11
            -> 操作数 %43 可以替换为常量（i32 1）
        Function: main, Block: Block12
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block12
            -> 操作数 %44 可以替换为常量（i32 200）
        Function: main, Block: Block12
            -> 操作数 %36 可以替换为常量（i32 2）
        Function: main, Block: Block12
            -> 操作数 %45 可以替换为常量（i32 99）
        Function: main, Block: Block13
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block13
            -> 操作数 %47 可以替换为常量（i32 5）
        Function: main, Block: Block13
            -> 操作数 %48 可以替换为常量（i32 1）
        Function: main, Block: Block14
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block14
            -> 操作数 %49 可以替换为常量（i32 200）
        Function: main, Block: Block14
            -> 操作数 %41 可以替换为常量（i32 3）
        Function: main, Block: Block14
            -> 操作数 %50 可以替换为常量（i32 99）
        Function: main, Block: Block15
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block15
            -> 操作数 %52 可以替换为常量（i32 6）
        Function: main, Block: Block15
            -> 操作数 %53 可以替换为常量（i32 1）
        Function: main, Block: Block16
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block16
            -> 操作数 %54 可以替换为常量（i32 200）
        Function: main, Block: Block16
            -> 操作数 %46 可以替换为常量（i32 4）
        Function: main, Block: Block16
            -> 操作数 %55 可以替换为常量（i32 99）
        Function: main, Block: Block17
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block17
            -> 操作数 %57 可以替换为常量（i32 7）
        Function: main, Block: Block17
            -> 操作数 %58 可以替换为常量（i32 1）
        Function: main, Block: Block18
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block18
            -> 操作数 %59 可以替换为常量（i32 200）
        Function: main, Block: Block18
            -> 操作数 %51 可以替换为常量（i32 5）
        Function: main, Block: Block18
            -> 操作数 %60 可以替换为常量（i32 99）
        Function: main, Block: Block19
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block19
            -> 操作数 %62 可以替换为常量（i32 8）
        Function: main, Block: Block19
            -> 操作数 %63 可以替换为常量（i32 1）
        Function: main, Block: Block20
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block20
            -> 操作数 %64 可以替换为常量（i32 200）
        Function: main, Block: Block20
            -> 操作数 %56 可以替换为常量（i32 6）
        Function: main, Block: Block20
            -> 操作数 %65 可以替换为常量（i32 99）
        Function: main, Block: Block21
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block21
            -> 操作数 %67 可以替换为常量（i32 9）
        Function: main, Block: Block21
            -> 操作数 %68 可以替换为常量（i32 1）
        Function: main, Block: Block22
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block22
            -> 操作数 %69 可以替换为常量（i32 200）
        Function: main, Block: Block22
            -> 操作数 %61 可以替换为常量（i32 7）
        Function: main, Block: Block22
            -> 操作数 %70 可以替换为常量（i32 99）
        Function: main, Block: Block23
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block23
            -> 操作数 %72 可以替换为常量（i32 10）
        Function: main, Block: Block23
            -> 操作数 %73 可以替换为常量（i32 1）
        Function: main, Block: Block24
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block24
            -> 操作数 %74 可以替换为常量（i32 200）
        Function: main, Block: Block24
            -> 操作数 %66 可以替换为常量（i32 8）
        Function: main, Block: Block24
            -> 操作数 %75 可以替换为常量（i32 99）
        Function: main, Block: Block25
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block25
            -> 操作数 %77 可以替换为常量（i32 11）
        Function: main, Block: Block25
            -> 操作数 %78 可以替换为常量（i32 1）
        Function: main, Block: Block26
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block26
            -> 操作数 %79 可以替换为常量（i32 200）
        Function: main, Block: Block26
            -> 操作数 %71 可以替换为常量（i32 9）
        Function: main, Block: Block26
            -> 操作数 %80 可以替换为常量（i32 99）
        Function: main, Block: Block27
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block27
            -> 操作数 %82 可以替换为常量（i32 12）
        Function: main, Block: Block27
            -> 操作数 %83 可以替换为常量（i32 1）
        Function: main, Block: Block28
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block28
            -> 操作数 %84 可以替换为常量（i32 200）
        Function: main, Block: Block28
            -> 操作数 %76 可以替换为常量（i32 10）
        Function: main, Block: Block28
            -> 操作数 %85 可以替换为常量（i32 99）
        Function: main, Block: Block29
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block29
            -> 操作数 %87 可以替换为常量（i32 13）
        Function: main, Block: Block29
            -> 操作数 %88 可以替换为常量（i32 1）
        Function: main, Block: Block30
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block30
            -> 操作数 %89 可以替换为常量（i32 200）
        Function: main, Block: Block30
            -> 操作数 %81 可以替换为常量（i32 11）
        Function: main, Block: Block30
            -> 操作数 %90 可以替换为常量（i32 99）
        Function: main, Block: Block31
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block31
            -> 操作数 %92 可以替换为常量（i32 14）
        Function: main, Block: Block31
            -> 操作数 %93 可以替换为常量（i32 1）
        Function: main, Block: Block32
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block32
            -> 操作数 %94 可以替换为常量（i32 200）
        Function: main, Block: Block32
            -> 操作数 %86 可以替换为常量（i32 12）
        Function: main, Block: Block32
            -> 操作数 %95 可以替换为常量（i32 99）
        Function: main, Block: Block33
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block33
            -> 操作数 %97 可以替换为常量（i32 15）
        Function: main, Block: Block33
            -> 操作数 %98 可以替换为常量（i32 1）
        Function: main, Block: Block34
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block34
            -> 操作数 %99 可以替换为常量（i32 200）
        Function: main, Block: Block34
            -> 操作数 %91 可以替换为常量（i32 13）
        Function: main, Block: Block34
            -> 操作数 %100 可以替换为常量（i32 99）
        Function: main, Block: Block35
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block35
            -> 操作数 %102 可以替换为常量（i32 16）
        Function: main, Block: Block35
            -> 操作数 %103 可以替换为常量（i32 1）
        Function: main, Block: Block36
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block36
            -> 操作数 %104 可以替换为常量（i32 200）
        Function: main, Block: Block36
            -> 操作数 %96 可以替换为常量（i32 14）
        Function: main, Block: Block36
            -> 操作数 %105 可以替换为常量（i32 99）
        Function: main, Block: Block37
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block37
            -> 操作数 %107 可以替换为常量（i32 17）
        Function: main, Block: Block37
            -> 操作数 %108 可以替换为常量（i32 1）
        Function: main, Block: Block38
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block38
            -> 操作数 %109 可以替换为常量（i32 200）
        Function: main, Block: Block38
            -> 操作数 %101 可以替换为常量（i32 15）
        Function: main, Block: Block38
            -> 操作数 %110 可以替换为常量（i32 99）
        Function: main, Block: Block39
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block39
            -> 操作数 %112 可以替换为常量（i32 18）
        Function: main, Block: Block39
            -> 操作数 %113 可以替换为常量（i32 1）
        Function: main, Block: Block40
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block40
            -> 操作数 %114 可以替换为常量（i32 200）
        Function: main, Block: Block40
            -> 操作数 %106 可以替换为常量（i32 16）
        Function: main, Block: Block40
            -> 操作数 %115 可以替换为常量（i32 99）
        Function: main, Block: Block41
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block41
            -> 操作数 %117 可以替换为常量（i32 19）
        Function: main, Block: Block41
            -> 操作数 %118 可以替换为常量（i32 1）
        Function: main, Block: Block42
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block42
            -> 操作数 %119 可以替换为常量（i32 200）
        Function: main, Block: Block42
            -> 操作数 %111 可以替换为常量（i32 17）
        Function: main, Block: Block42
            -> 操作数 %120 可以替换为常量（i32 99）
        Function: main, Block: Block43
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block43
            -> 操作数 %122 可以替换为常量（i32 20）
        Function: main, Block: Block43
            -> 操作数 %123 可以替换为常量（i32 1）
        Function: main, Block: Block44
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block44
            -> 操作数 %124 可以替换为常量（i32 200）
        Function: main, Block: Block44
            -> 操作数 %116 可以替换为常量（i32 18）
        Function: main, Block: Block44
            -> 操作数 %125 可以替换为常量（i32 99）
        Function: main, Block: Block45
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block45
            -> 操作数 %127 可以替换为常量（i32 21）
        Function: main, Block: Block45
            -> 操作数 %128 可以替换为常量（i32 1）
        Function: main, Block: Block46
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block46
            -> 操作数 %129 可以替换为常量（i32 200）
        Function: main, Block: Block46
            -> 操作数 %121 可以替换为常量（i32 19）
        Function: main, Block: Block46
            -> 操作数 %130 可以替换为常量（i32 99）
        Function: main, Block: Block47
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block47
            -> 操作数 %132 可以替换为常量（i32 22）
        Function: main, Block: Block47
            -> 操作数 %133 可以替换为常量（i32 1）
        Function: main, Block: Block48
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block48
            -> 操作数 %134 可以替换为常量（i32 200）
        Function: main, Block: Block48
            -> 操作数 %126 可以替换为常量（i32 20）
        Function: main, Block: Block48
            -> 操作数 %135 可以替换为常量（i32 99）
        Function: main, Block: Block49
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block49
            -> 操作数 %137 可以替换为常量（i32 23）
        Function: main, Block: Block49
            -> 操作数 %138 可以替换为常量（i32 1）
        Function: main, Block: Block50
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block50
            -> 操作数 %139 可以替换为常量（i32 200）
        Function: main, Block: Block50
            -> 操作数 %131 可以替换为常量（i32 21）
        Function: main, Block: Block50
            -> 操作数 %140 可以替换为常量（i32 99）
        Function: main, Block: Block51
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block51
            -> 操作数 %142 可以替换为常量（i32 24）
        Function: main, Block: Block51
            -> 操作数 %143 可以替换为常量（i32 1）
        Function: main, Block: Block52
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block52
            -> 操作数 %144 可以替换为常量（i32 200）
        Function: main, Block: Block52
            -> 操作数 %136 可以替换为常量（i32 22）
        Function: main, Block: Block52
            -> 操作数 %145 可以替换为常量（i32 99）
        Function: main, Block: Block53
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block53
            -> 操作数 %147 可以替换为常量（i32 25）
        Function: main, Block: Block53
            -> 操作数 %148 可以替换为常量（i32 1）
        Function: main, Block: Block54
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block54
            -> 操作数 %149 可以替换为常量（i32 200）
        Function: main, Block: Block54
            -> 操作数 %141 可以替换为常量（i32 23）
        Function: main, Block: Block54
            -> 操作数 %150 可以替换为常量（i32 99）
        Function: main, Block: Block55
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block55
            -> 操作数 %152 可以替换为常量（i32 26）
        Function: main, Block: Block55
            -> 操作数 %153 可以替换为常量（i32 1）
        Function: main, Block: Block56
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block56
            -> 操作数 %154 可以替换为常量（i32 200）
        Function: main, Block: Block56
            -> 操作数 %146 可以替换为常量（i32 24）
        Function: main, Block: Block56
            -> 操作数 %155 可以替换为常量（i32 99）
        Function: main, Block: Block57
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block57
            -> 操作数 %157 可以替换为常量（i32 27）
        Function: main, Block: Block57
            -> 操作数 %158 可以替换为常量（i32 1）
        Function: main, Block: Block58
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block58
            -> 操作数 %159 可以替换为常量（i32 200）
        Function: main, Block: Block58
            -> 操作数 %151 可以替换为常量（i32 25）
        Function: main, Block: Block58
            -> 操作数 %160 可以替换为常量（i32 99）
        Function: main, Block: Block59
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block59
            -> 操作数 %162 可以替换为常量（i32 28）
        Function: main, Block: Block59
            -> 操作数 %163 可以替换为常量（i32 1）
        Function: main, Block: Block60
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block60
            -> 操作数 %164 可以替换为常量（i32 200）
        Function: main, Block: Block60
            -> 操作数 %156 可以替换为常量（i32 26）
        Function: main, Block: Block60
            -> 操作数 %165 可以替换为常量（i32 99）
        Function: main, Block: Block61
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block61
            -> 操作数 %167 可以替换为常量（i32 29）
        Function: main, Block: Block61
            -> 操作数 %168 可以替换为常量（i32 1）
        Function: main, Block: Block62
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block62
            -> 操作数 %169 可以替换为常量（i32 200）
        Function: main, Block: Block62
            -> 操作数 %161 可以替换为常量（i32 27）
        Function: main, Block: Block62
            -> 操作数 %170 可以替换为常量（i32 99）
        Function: main, Block: Block63
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block63
            -> 操作数 %172 可以替换为常量（i32 30）
        Function: main, Block: Block63
            -> 操作数 %173 可以替换为常量（i32 1）
        Function: main, Block: Block64
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block64
            -> 操作数 %174 可以替换为常量（i32 200）
        Function: main, Block: Block64
            -> 操作数 %166 可以替换为常量（i32 28）
        Function: main, Block: Block64
            -> 操作数 %175 可以替换为常量（i32 99）
        Function: main, Block: Block65
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block65
            -> 操作数 %177 可以替换为常量（i32 31）
        Function: main, Block: Block65
            -> 操作数 %178 可以替换为常量（i32 1）
        Function: main, Block: Block66
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block66
            -> 操作数 %179 可以替换为常量（i32 200）
        Function: main, Block: Block66
            -> 操作数 %171 可以替换为常量（i32 29）
        Function: main, Block: Block66
            -> 操作数 %180 可以替换为常量（i32 99）
        Function: main, Block: Block67
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block67
            -> 操作数 %182 可以替换为常量（i32 32）
        Function: main, Block: Block67
            -> 操作数 %183 可以替换为常量（i32 1）
        Function: main, Block: Block68
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block68
            -> 操作数 %184 可以替换为常量（i32 200）
        Function: main, Block: Block68
            -> 操作数 %176 可以替换为常量（i32 30）
        Function: main, Block: Block68
            -> 操作数 %185 可以替换为常量（i32 99）
        Function: main, Block: Block69
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block69
            -> 操作数 %187 可以替换为常量（i32 33）
        Function: main, Block: Block69
            -> 操作数 %188 可以替换为常量（i32 1）
        Function: main, Block: Block70
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block70
            -> 操作数 %189 可以替换为常量（i32 200）
        Function: main, Block: Block70
            -> 操作数 %181 可以替换为常量（i32 31）
        Function: main, Block: Block70
            -> 操作数 %190 可以替换为常量（i32 99）
        Function: main, Block: Block71
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block71
            -> 操作数 %192 可以替换为常量（i32 34）
        Function: main, Block: Block71
            -> 操作数 %193 可以替换为常量（i32 1）
        Function: main, Block: Block72
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block72
            -> 操作数 %194 可以替换为常量（i32 200）
        Function: main, Block: Block72
            -> 操作数 %186 可以替换为常量（i32 32）
        Function: main, Block: Block72
            -> 操作数 %195 可以替换为常量（i32 99）
        Function: main, Block: Block73
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block73
            -> 操作数 %197 可以替换为常量（i32 35）
        Function: main, Block: Block73
            -> 操作数 %198 可以替换为常量（i32 1）
        Function: main, Block: Block74
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block74
            -> 操作数 %199 可以替换为常量（i32 200）
        Function: main, Block: Block74
            -> 操作数 %191 可以替换为常量（i32 33）
        Function: main, Block: Block74
            -> 操作数 %200 可以替换为常量（i32 99）
        Function: main, Block: Block75
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block75
            -> 操作数 %202 可以替换为常量（i32 36）
        Function: main, Block: Block75
            -> 操作数 %203 可以替换为常量（i32 1）
        Function: main, Block: Block76
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block76
            -> 操作数 %204 可以替换为常量（i32 200）
        Function: main, Block: Block76
            -> 操作数 %196 可以替换为常量（i32 34）
        Function: main, Block: Block76
            -> 操作数 %205 可以替换为常量（i32 99）
        Function: main, Block: Block77
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block77
            -> 操作数 %207 可以替换为常量（i32 37）
        Function: main, Block: Block77
            -> 操作数 %208 可以替换为常量（i32 1）
        Function: main, Block: Block78
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block78
            -> 操作数 %209 可以替换为常量（i32 200）
        Function: main, Block: Block78
            -> 操作数 %201 可以替换为常量（i32 35）
        Function: main, Block: Block78
            -> 操作数 %210 可以替换为常量（i32 99）
        Function: main, Block: Block79
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block79
            -> 操作数 %212 可以替换为常量（i32 38）
        Function: main, Block: Block79
            -> 操作数 %213 可以替换为常量（i32 1）
        Function: main, Block: Block80
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block80
            -> 操作数 %214 可以替换为常量（i32 200）
        Function: main, Block: Block80
            -> 操作数 %206 可以替换为常量（i32 36）
        Function: main, Block: Block80
            -> 操作数 %215 可以替换为常量（i32 99）
        Function: main, Block: Block81
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block81
            -> 操作数 %217 可以替换为常量（i32 39）
        Function: main, Block: Block81
            -> 操作数 %218 可以替换为常量（i32 1）
        Function: main, Block: Block82
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block82
            -> 操作数 %219 可以替换为常量（i32 200）
        Function: main, Block: Block82
            -> 操作数 %211 可以替换为常量（i32 37）
        Function: main, Block: Block82
            -> 操作数 %220 可以替换为常量（i32 99）
        Function: main, Block: Block83
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block83
            -> 操作数 %222 可以替换为常量（i32 40）
        Function: main, Block: Block83
            -> 操作数 %223 可以替换为常量（i32 1）
        Function: main, Block: Block84
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block84
            -> 操作数 %224 可以替换为常量（i32 200）
        Function: main, Block: Block84
            -> 操作数 %216 可以替换为常量（i32 38）
        Function: main, Block: Block84
            -> 操作数 %225 可以替换为常量（i32 99）
        Function: main, Block: Block85
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block85
            -> 操作数 %227 可以替换为常量（i32 41）
        Function: main, Block: Block85
            -> 操作数 %228 可以替换为常量（i32 1）
        Function: main, Block: Block86
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block86
            -> 操作数 %229 可以替换为常量（i32 200）
        Function: main, Block: Block86
            -> 操作数 %221 可以替换为常量（i32 39）
        Function: main, Block: Block86
            -> 操作数 %230 可以替换为常量（i32 99）
        Function: main, Block: Block87
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block87
            -> 操作数 %232 可以替换为常量（i32 42）
        Function: main, Block: Block87
            -> 操作数 %233 可以替换为常量（i32 1）
        Function: main, Block: Block88
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block88
            -> 操作数 %234 可以替换为常量（i32 200）
        Function: main, Block: Block88
            -> 操作数 %226 可以替换为常量（i32 40）
        Function: main, Block: Block88
            -> 操作数 %235 可以替换为常量（i32 99）
        Function: main, Block: Block89
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block89
            -> 操作数 %237 可以替换为常量（i32 43）
        Function: main, Block: Block89
            -> 操作数 %238 可以替换为常量（i32 1）
        Function: main, Block: Block90
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block90
            -> 操作数 %239 可以替换为常量（i32 200）
        Function: main, Block: Block90
            -> 操作数 %231 可以替换为常量（i32 41）
        Function: main, Block: Block90
            -> 操作数 %240 可以替换为常量（i32 99）
        Function: main, Block: Block91
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block91
            -> 操作数 %242 可以替换为常量（i32 44）
        Function: main, Block: Block91
            -> 操作数 %243 可以替换为常量（i32 1）
        Function: main, Block: Block92
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block92
            -> 操作数 %244 可以替换为常量（i32 200）
        Function: main, Block: Block92
            -> 操作数 %236 可以替换为常量（i32 42）
        Function: main, Block: Block92
            -> 操作数 %245 可以替换为常量（i32 99）
        Function: main, Block: Block93
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block93
            -> 操作数 %247 可以替换为常量（i32 45）
        Function: main, Block: Block93
            -> 操作数 %248 可以替换为常量（i32 1）
        Function: main, Block: Block94
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block94
            -> 操作数 %249 可以替换为常量（i32 200）
        Function: main, Block: Block94
            -> 操作数 %241 可以替换为常量（i32 43）
        Function: main, Block: Block94
            -> 操作数 %250 可以替换为常量（i32 99）
        Function: main, Block: Block95
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block95
            -> 操作数 %252 可以替换为常量（i32 46）
        Function: main, Block: Block95
            -> 操作数 %253 可以替换为常量（i32 1）
        Function: main, Block: Block96
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block96
            -> 操作数 %254 可以替换为常量（i32 200）
        Function: main, Block: Block96
            -> 操作数 %246 可以替换为常量（i32 44）
        Function: main, Block: Block96
            -> 操作数 %255 可以替换为常量（i32 99）
        Function: main, Block: Block97
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block97
            -> 操作数 %257 可以替换为常量（i32 47）
        Function: main, Block: Block97
            -> 操作数 %258 可以替换为常量（i32 1）
        Function: main, Block: Block98
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block98
            -> 操作数 %259 可以替换为常量（i32 200）
        Function: main, Block: Block98
            -> 操作数 %251 可以替换为常量（i32 45）
        Function: main, Block: Block98
            -> 操作数 %260 可以替换为常量（i32 99）
        Function: main, Block: Block99
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block99
            -> 操作数 %262 可以替换为常量（i32 48）
        Function: main, Block: Block99
            -> 操作数 %263 可以替换为常量（i32 1）
        Function: main, Block: Block100
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block100
            -> 操作数 %264 可以替换为常量（i32 200）
        Function: main, Block: Block100
            -> 操作数 %256 可以替换为常量（i32 46）
        Function: main, Block: Block100
            -> 操作数 %265 可以替换为常量（i32 99）
        Function: main, Block: Block101
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block101
            -> 操作数 %267 可以替换为常量（i32 49）
        Function: main, Block: Block101
            -> 操作数 %268 可以替换为常量（i32 1）
        Function: main, Block: Block102
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block102
            -> 操作数 %269 可以替换为常量（i32 200）
        Function: main, Block: Block102
            -> 操作数 %261 可以替换为常量（i32 47）
        Function: main, Block: Block102
            -> 操作数 %270 可以替换为常量（i32 99）
        Function: main, Block: Block103
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block103
            -> 操作数 %272 可以替换为常量（i32 50）
        Function: main, Block: Block103
            -> 操作数 %273 可以替换为常量（i32 1）
        Function: main, Block: Block104
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block104
            -> 操作数 %274 可以替换为常量（i32 200）
        Function: main, Block: Block104
            -> 操作数 %266 可以替换为常量（i32 48）
        Function: main, Block: Block104
            -> 操作数 %275 可以替换为常量（i32 99）
        Function: main, Block: Block105
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block105
            -> 操作数 %277 可以替换为常量（i32 51）
        Function: main, Block: Block105
            -> 操作数 %278 可以替换为常量（i32 1）
        Function: main, Block: Block106
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block106
            -> 操作数 %279 可以替换为常量（i32 200）
        Function: main, Block: Block106
            -> 操作数 %271 可以替换为常量（i32 49）
        Function: main, Block: Block106
            -> 操作数 %280 可以替换为常量（i32 99）
        Function: main, Block: Block107
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block107
            -> 操作数 %282 可以替换为常量（i32 52）
        Function: main, Block: Block107
            -> 操作数 %283 可以替换为常量（i32 1）
        Function: main, Block: Block108
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block108
            -> 操作数 %284 可以替换为常量（i32 200）
        Function: main, Block: Block108
            -> 操作数 %276 可以替换为常量（i32 50）
        Function: main, Block: Block108
            -> 操作数 %285 可以替换为常量（i32 99）
        Function: main, Block: Block109
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block109
            -> 操作数 %287 可以替换为常量（i32 53）
        Function: main, Block: Block109
            -> 操作数 %288 可以替换为常量（i32 1）
        Function: main, Block: Block110
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block110
            -> 操作数 %289 可以替换为常量（i32 200）
        Function: main, Block: Block110
            -> 操作数 %281 可以替换为常量（i32 51）
        Function: main, Block: Block110
            -> 操作数 %290 可以替换为常量（i32 99）
        Function: main, Block: Block111
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block111
            -> 操作数 %292 可以替换为常量（i32 54）
        Function: main, Block: Block111
            -> 操作数 %293 可以替换为常量（i32 1）
        Function: main, Block: Block112
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block112
            -> 操作数 %294 可以替换为常量（i32 200）
        Function: main, Block: Block112
            -> 操作数 %286 可以替换为常量（i32 52）
        Function: main, Block: Block112
            -> 操作数 %295 可以替换为常量（i32 99）
        Function: main, Block: Block113
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block113
            -> 操作数 %297 可以替换为常量（i32 55）
        Function: main, Block: Block113
            -> 操作数 %298 可以替换为常量（i32 1）
        Function: main, Block: Block114
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block114
            -> 操作数 %299 可以替换为常量（i32 200）
        Function: main, Block: Block114
            -> 操作数 %291 可以替换为常量（i32 53）
        Function: main, Block: Block114
            -> 操作数 %300 可以替换为常量（i32 99）
        Function: main, Block: Block115
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block115
            -> 操作数 %302 可以替换为常量（i32 56）
        Function: main, Block: Block115
            -> 操作数 %303 可以替换为常量（i32 1）
        Function: main, Block: Block116
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block116
            -> 操作数 %304 可以替换为常量（i32 200）
        Function: main, Block: Block116
            -> 操作数 %296 可以替换为常量（i32 54）
        Function: main, Block: Block116
            -> 操作数 %305 可以替换为常量（i32 99）
        Function: main, Block: Block117
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block117
            -> 操作数 %307 可以替换为常量（i32 57）
        Function: main, Block: Block117
            -> 操作数 %308 可以替换为常量（i32 1）
        Function: main, Block: Block118
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block118
            -> 操作数 %309 可以替换为常量（i32 200）
        Function: main, Block: Block118
            -> 操作数 %301 可以替换为常量（i32 55）
        Function: main, Block: Block118
            -> 操作数 %310 可以替换为常量（i32 99）
        Function: main, Block: Block119
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block119
            -> 操作数 %312 可以替换为常量（i32 58）
        Function: main, Block: Block119
            -> 操作数 %313 可以替换为常量（i32 1）
        Function: main, Block: Block120
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block120
            -> 操作数 %314 可以替换为常量（i32 200）
        Function: main, Block: Block120
            -> 操作数 %306 可以替换为常量（i32 56）
        Function: main, Block: Block120
            -> 操作数 %315 可以替换为常量（i32 99）
        Function: main, Block: Block121
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block121
            -> 操作数 %317 可以替换为常量（i32 59）
        Function: main, Block: Block121
            -> 操作数 %318 可以替换为常量（i32 1）
        Function: main, Block: Block122
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block122
            -> 操作数 %319 可以替换为常量（i32 200）
        Function: main, Block: Block122
            -> 操作数 %311 可以替换为常量（i32 57）
        Function: main, Block: Block122
            -> 操作数 %320 可以替换为常量（i32 99）
        Function: main, Block: Block123
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block123
            -> 操作数 %322 可以替换为常量（i32 60）
        Function: main, Block: Block123
            -> 操作数 %323 可以替换为常量（i32 1）
        Function: main, Block: Block124
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block124
            -> 操作数 %324 可以替换为常量（i32 200）
        Function: main, Block: Block124
            -> 操作数 %316 可以替换为常量（i32 58）
        Function: main, Block: Block124
            -> 操作数 %325 可以替换为常量（i32 99）
        Function: main, Block: Block125
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block125
            -> 操作数 %327 可以替换为常量（i32 61）
        Function: main, Block: Block125
            -> 操作数 %328 可以替换为常量（i32 1）
        Function: main, Block: Block126
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block126
            -> 操作数 %329 可以替换为常量（i32 200）
        Function: main, Block: Block126
            -> 操作数 %321 可以替换为常量（i32 59）
        Function: main, Block: Block126
            -> 操作数 %330 可以替换为常量（i32 99）
        Function: main, Block: Block127
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block127
            -> 操作数 %332 可以替换为常量（i32 62）
        Function: main, Block: Block127
            -> 操作数 %333 可以替换为常量（i32 1）
        Function: main, Block: Block128
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block128
            -> 操作数 %334 可以替换为常量（i32 200）
        Function: main, Block: Block128
            -> 操作数 %326 可以替换为常量（i32 60）
        Function: main, Block: Block128
            -> 操作数 %335 可以替换为常量（i32 99）
        Function: main, Block: Block129
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block129
            -> 操作数 %337 可以替换为常量（i32 63）
        Function: main, Block: Block129
            -> 操作数 %338 可以替换为常量（i32 1）
        Function: main, Block: Block130
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block130
            -> 操作数 %339 可以替换为常量（i32 200）
        Function: main, Block: Block130
            -> 操作数 %331 可以替换为常量（i32 61）
        Function: main, Block: Block130
            -> 操作数 %340 可以替换为常量（i32 99）
        Function: main, Block: Block131
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block131
            -> 操作数 %342 可以替换为常量（i32 64）
        Function: main, Block: Block131
            -> 操作数 %343 可以替换为常量（i32 1）
        Function: main, Block: Block132
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block132
            -> 操作数 %344 可以替换为常量（i32 200）
        Function: main, Block: Block132
            -> 操作数 %336 可以替换为常量（i32 62）
        Function: main, Block: Block132
            -> 操作数 %345 可以替换为常量（i32 99）
        Function: main, Block: Block133
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block133
            -> 操作数 %347 可以替换为常量（i32 65）
        Function: main, Block: Block133
            -> 操作数 %348 可以替换为常量（i32 1）
        Function: main, Block: Block134
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block134
            -> 操作数 %349 可以替换为常量（i32 200）
        Function: main, Block: Block134
            -> 操作数 %341 可以替换为常量（i32 63）
        Function: main, Block: Block134
            -> 操作数 %350 可以替换为常量（i32 99）
        Function: main, Block: Block135
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block135
            -> 操作数 %352 可以替换为常量（i32 66）
        Function: main, Block: Block135
            -> 操作数 %353 可以替换为常量（i32 1）
        Function: main, Block: Block136
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block136
            -> 操作数 %354 可以替换为常量（i32 200）
        Function: main, Block: Block136
            -> 操作数 %346 可以替换为常量（i32 64）
        Function: main, Block: Block136
            -> 操作数 %355 可以替换为常量（i32 99）
        Function: main, Block: Block137
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block137
            -> 操作数 %357 可以替换为常量（i32 67）
        Function: main, Block: Block137
            -> 操作数 %358 可以替换为常量（i32 1）
        Function: main, Block: Block138
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block138
            -> 操作数 %359 可以替换为常量（i32 200）
        Function: main, Block: Block138
            -> 操作数 %351 可以替换为常量（i32 65）
        Function: main, Block: Block138
            -> 操作数 %360 可以替换为常量（i32 99）
        Function: main, Block: Block139
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block139
            -> 操作数 %362 可以替换为常量（i32 68）
        Function: main, Block: Block139
            -> 操作数 %363 可以替换为常量（i32 1）
        Function: main, Block: Block140
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block140
            -> 操作数 %364 可以替换为常量（i32 200）
        Function: main, Block: Block140
            -> 操作数 %356 可以替换为常量（i32 66）
        Function: main, Block: Block140
            -> 操作数 %365 可以替换为常量（i32 99）
        Function: main, Block: Block141
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block141
            -> 操作数 %367 可以替换为常量（i32 69）
        Function: main, Block: Block141
            -> 操作数 %368 可以替换为常量（i32 1）
        Function: main, Block: Block142
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block142
            -> 操作数 %369 可以替换为常量（i32 200）
        Function: main, Block: Block142
            -> 操作数 %361 可以替换为常量（i32 67）
        Function: main, Block: Block142
            -> 操作数 %370 可以替换为常量（i32 99）
        Function: main, Block: Block143
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block143
            -> 操作数 %372 可以替换为常量（i32 70）
        Function: main, Block: Block143
            -> 操作数 %373 可以替换为常量（i32 1）
        Function: main, Block: Block144
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block144
            -> 操作数 %374 可以替换为常量（i32 200）
        Function: main, Block: Block144
            -> 操作数 %366 可以替换为常量（i32 68）
        Function: main, Block: Block144
            -> 操作数 %375 可以替换为常量（i32 99）
        Function: main, Block: Block145
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block145
            -> 操作数 %377 可以替换为常量（i32 71）
        Function: main, Block: Block145
            -> 操作数 %378 可以替换为常量（i32 1）
        Function: main, Block: Block146
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block146
            -> 操作数 %379 可以替换为常量（i32 200）
        Function: main, Block: Block146
            -> 操作数 %371 可以替换为常量（i32 69）
        Function: main, Block: Block146
            -> 操作数 %380 可以替换为常量（i32 99）
        Function: main, Block: Block147
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block147
            -> 操作数 %382 可以替换为常量（i32 72）
        Function: main, Block: Block147
            -> 操作数 %383 可以替换为常量（i32 1）
        Function: main, Block: Block148
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block148
            -> 操作数 %384 可以替换为常量（i32 200）
        Function: main, Block: Block148
            -> 操作数 %376 可以替换为常量（i32 70）
        Function: main, Block: Block148
            -> 操作数 %385 可以替换为常量（i32 99）
        Function: main, Block: Block149
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block149
            -> 操作数 %387 可以替换为常量（i32 73）
        Function: main, Block: Block149
            -> 操作数 %388 可以替换为常量（i32 1）
        Function: main, Block: Block150
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block150
            -> 操作数 %389 可以替换为常量（i32 200）
        Function: main, Block: Block150
            -> 操作数 %381 可以替换为常量（i32 71）
        Function: main, Block: Block150
            -> 操作数 %390 可以替换为常量（i32 99）
        Function: main, Block: Block151
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block151
            -> 操作数 %392 可以替换为常量（i32 74）
        Function: main, Block: Block151
            -> 操作数 %393 可以替换为常量（i32 1）
        Function: main, Block: Block152
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block152
            -> 操作数 %394 可以替换为常量（i32 200）
        Function: main, Block: Block152
            -> 操作数 %386 可以替换为常量（i32 72）
        Function: main, Block: Block152
            -> 操作数 %395 可以替换为常量（i32 99）
        Function: main, Block: Block153
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block153
            -> 操作数 %397 可以替换为常量（i32 75）
        Function: main, Block: Block153
            -> 操作数 %398 可以替换为常量（i32 1）
        Function: main, Block: Block154
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block154
            -> 操作数 %399 可以替换为常量（i32 200）
        Function: main, Block: Block154
            -> 操作数 %391 可以替换为常量（i32 73）
        Function: main, Block: Block154
            -> 操作数 %400 可以替换为常量（i32 99）
        Function: main, Block: Block155
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block155
            -> 操作数 %402 可以替换为常量（i32 76）
        Function: main, Block: Block155
            -> 操作数 %403 可以替换为常量（i32 1）
        Function: main, Block: Block156
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block156
            -> 操作数 %404 可以替换为常量（i32 200）
        Function: main, Block: Block156
            -> 操作数 %396 可以替换为常量（i32 74）
        Function: main, Block: Block156
            -> 操作数 %405 可以替换为常量（i32 99）
        Function: main, Block: Block157
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block157
            -> 操作数 %407 可以替换为常量（i32 77）
        Function: main, Block: Block157
            -> 操作数 %408 可以替换为常量（i32 1）
        Function: main, Block: Block158
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block158
            -> 操作数 %409 可以替换为常量（i32 200）
        Function: main, Block: Block158
            -> 操作数 %401 可以替换为常量（i32 75）
        Function: main, Block: Block158
            -> 操作数 %410 可以替换为常量（i32 99）
        Function: main, Block: Block159
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block159
            -> 操作数 %412 可以替换为常量（i32 78）
        Function: main, Block: Block159
            -> 操作数 %413 可以替换为常量（i32 1）
        Function: main, Block: Block160
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block160
            -> 操作数 %414 可以替换为常量（i32 200）
        Function: main, Block: Block160
            -> 操作数 %406 可以替换为常量（i32 76）
        Function: main, Block: Block160
            -> 操作数 %415 可以替换为常量（i32 99）
        Function: main, Block: Block161
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block161
            -> 操作数 %417 可以替换为常量（i32 79）
        Function: main, Block: Block161
            -> 操作数 %418 可以替换为常量（i32 1）
        Function: main, Block: Block162
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block162
            -> 操作数 %419 可以替换为常量（i32 200）
        Function: main, Block: Block162
            -> 操作数 %411 可以替换为常量（i32 77）
        Function: main, Block: Block162
            -> 操作数 %420 可以替换为常量（i32 99）
        Function: main, Block: Block163
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block163
            -> 操作数 %422 可以替换为常量（i32 80）
        Function: main, Block: Block163
            -> 操作数 %423 可以替换为常量（i32 1）
        Function: main, Block: Block164
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block164
            -> 操作数 %424 可以替换为常量（i32 200）
        Function: main, Block: Block164
            -> 操作数 %416 可以替换为常量（i32 78）
        Function: main, Block: Block164
            -> 操作数 %425 可以替换为常量（i32 99）
        Function: main, Block: Block165
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block165
            -> 操作数 %427 可以替换为常量（i32 81）
        Function: main, Block: Block165
            -> 操作数 %428 可以替换为常量（i32 1）
        Function: main, Block: Block166
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block166
            -> 操作数 %429 可以替换为常量（i32 200）
        Function: main, Block: Block166
            -> 操作数 %421 可以替换为常量（i32 79）
        Function: main, Block: Block166
            -> 操作数 %430 可以替换为常量（i32 99）
        Function: main, Block: Block167
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block167
            -> 操作数 %432 可以替换为常量（i32 82）
        Function: main, Block: Block167
            -> 操作数 %433 可以替换为常量（i32 1）
        Function: main, Block: Block168
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block168
            -> 操作数 %434 可以替换为常量（i32 200）
        Function: main, Block: Block168
            -> 操作数 %426 可以替换为常量（i32 80）
        Function: main, Block: Block168
            -> 操作数 %435 可以替换为常量（i32 99）
        Function: main, Block: Block169
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block169
            -> 操作数 %437 可以替换为常量（i32 83）
        Function: main, Block: Block169
            -> 操作数 %438 可以替换为常量（i32 1）
        Function: main, Block: Block170
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block170
            -> 操作数 %439 可以替换为常量（i32 200）
        Function: main, Block: Block170
            -> 操作数 %431 可以替换为常量（i32 81）
        Function: main, Block: Block170
            -> 操作数 %440 可以替换为常量（i32 99）
        Function: main, Block: Block171
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block171
            -> 操作数 %442 可以替换为常量（i32 84）
        Function: main, Block: Block171
            -> 操作数 %443 可以替换为常量（i32 1）
        Function: main, Block: Block172
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block172
            -> 操作数 %444 可以替换为常量（i32 200）
        Function: main, Block: Block172
            -> 操作数 %436 可以替换为常量（i32 82）
        Function: main, Block: Block172
            -> 操作数 %445 可以替换为常量（i32 99）
        Function: main, Block: Block173
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block173
            -> 操作数 %447 可以替换为常量（i32 85）
        Function: main, Block: Block173
            -> 操作数 %448 可以替换为常量（i32 1）
        Function: main, Block: Block174
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block174
            -> 操作数 %449 可以替换为常量（i32 200）
        Function: main, Block: Block174
            -> 操作数 %441 可以替换为常量（i32 83）
        Function: main, Block: Block174
            -> 操作数 %450 可以替换为常量（i32 99）
        Function: main, Block: Block175
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block175
            -> 操作数 %452 可以替换为常量（i32 86）
        Function: main, Block: Block175
            -> 操作数 %453 可以替换为常量（i32 1）
        Function: main, Block: Block176
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block176
            -> 操作数 %454 可以替换为常量（i32 200）
        Function: main, Block: Block176
            -> 操作数 %446 可以替换为常量（i32 84）
        Function: main, Block: Block176
            -> 操作数 %455 可以替换为常量（i32 99）
        Function: main, Block: Block177
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block177
            -> 操作数 %457 可以替换为常量（i32 87）
        Function: main, Block: Block177
            -> 操作数 %458 可以替换为常量（i32 1）
        Function: main, Block: Block178
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block178
            -> 操作数 %459 可以替换为常量（i32 200）
        Function: main, Block: Block178
            -> 操作数 %451 可以替换为常量（i32 85）
        Function: main, Block: Block178
            -> 操作数 %460 可以替换为常量（i32 99）
        Function: main, Block: Block179
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block179
            -> 操作数 %462 可以替换为常量（i32 88）
        Function: main, Block: Block179
            -> 操作数 %463 可以替换为常量（i32 1）
        Function: main, Block: Block180
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block180
            -> 操作数 %464 可以替换为常量（i32 200）
        Function: main, Block: Block180
            -> 操作数 %456 可以替换为常量（i32 86）
        Function: main, Block: Block180
            -> 操作数 %465 可以替换为常量（i32 99）
        Function: main, Block: Block181
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block181
            -> 操作数 %467 可以替换为常量（i32 89）
        Function: main, Block: Block181
            -> 操作数 %468 可以替换为常量（i32 1）
        Function: main, Block: Block182
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block182
            -> 操作数 %469 可以替换为常量（i32 200）
        Function: main, Block: Block182
            -> 操作数 %461 可以替换为常量（i32 87）
        Function: main, Block: Block182
            -> 操作数 %470 可以替换为常量（i32 99）
        Function: main, Block: Block183
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block183
            -> 操作数 %472 可以替换为常量（i32 90）
        Function: main, Block: Block183
            -> 操作数 %473 可以替换为常量（i32 1）
        Function: main, Block: Block184
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block184
            -> 操作数 %474 可以替换为常量（i32 200）
        Function: main, Block: Block184
            -> 操作数 %466 可以替换为常量（i32 88）
        Function: main, Block: Block184
            -> 操作数 %475 可以替换为常量（i32 99）
        Function: main, Block: Block185
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block185
            -> 操作数 %477 可以替换为常量（i32 91）
        Function: main, Block: Block185
            -> 操作数 %478 可以替换为常量（i32 1）
        Function: main, Block: Block186
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block186
            -> 操作数 %479 可以替换为常量（i32 200）
        Function: main, Block: Block186
            -> 操作数 %471 可以替换为常量（i32 89）
        Function: main, Block: Block186
            -> 操作数 %480 可以替换为常量（i32 99）
        Function: main, Block: Block187
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block187
            -> 操作数 %482 可以替换为常量（i32 92）
        Function: main, Block: Block187
            -> 操作数 %483 可以替换为常量（i32 1）
        Function: main, Block: Block188
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block188
            -> 操作数 %484 可以替换为常量（i32 200）
        Function: main, Block: Block188
            -> 操作数 %476 可以替换为常量（i32 90）
        Function: main, Block: Block188
            -> 操作数 %485 可以替换为常量（i32 99）
        Function: main, Block: Block189
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block189
            -> 操作数 %487 可以替换为常量（i32 93）
        Function: main, Block: Block189
            -> 操作数 %488 可以替换为常量（i32 1）
        Function: main, Block: Block190
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block190
            -> 操作数 %489 可以替换为常量（i32 200）
        Function: main, Block: Block190
            -> 操作数 %481 可以替换为常量（i32 91）
        Function: main, Block: Block190
            -> 操作数 %490 可以替换为常量（i32 99）
        Function: main, Block: Block191
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block191
            -> 操作数 %492 可以替换为常量（i32 94）
        Function: main, Block: Block191
            -> 操作数 %493 可以替换为常量（i32 1）
        Function: main, Block: Block192
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block192
            -> 操作数 %494 可以替换为常量（i32 200）
        Function: main, Block: Block192
            -> 操作数 %486 可以替换为常量（i32 92）
        Function: main, Block: Block192
            -> 操作数 %495 可以替换为常量（i32 99）
        Function: main, Block: Block193
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block193
            -> 操作数 %497 可以替换为常量（i32 95）
        Function: main, Block: Block193
            -> 操作数 %498 可以替换为常量（i32 1）
        Function: main, Block: Block194
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block194
            -> 操作数 %499 可以替换为常量（i32 200）
        Function: main, Block: Block194
            -> 操作数 %491 可以替换为常量（i32 93）
        Function: main, Block: Block194
            -> 操作数 %500 可以替换为常量（i32 99）
        Function: main, Block: Block195
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block195
            -> 操作数 %502 可以替换为常量（i32 96）
        Function: main, Block: Block195
            -> 操作数 %503 可以替换为常量（i32 1）
        Function: main, Block: Block196
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block196
            -> 操作数 %504 可以替换为常量（i32 200）
        Function: main, Block: Block196
            -> 操作数 %496 可以替换为常量（i32 94）
        Function: main, Block: Block196
            -> 操作数 %505 可以替换为常量（i32 99）
        Function: main, Block: Block197
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block197
            -> 操作数 %507 可以替换为常量（i32 97）
        Function: main, Block: Block197
            -> 操作数 %508 可以替换为常量（i32 1）
        Function: main, Block: Block198
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block198
            -> 操作数 %509 可以替换为常量（i32 200）
        Function: main, Block: Block198
            -> 操作数 %501 可以替换为常量（i32 95）
        Function: main, Block: Block198
            -> 操作数 %510 可以替换为常量（i32 99）
        Function: main, Block: Block199
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block199
            -> 操作数 %512 可以替换为常量（i32 98）
        Function: main, Block: Block199
            -> 操作数 %513 可以替换为常量（i32 1）
        Function: main, Block: Block200
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block200
            -> 操作数 %514 可以替换为常量（i32 200）
        Function: main, Block: Block200
            -> 操作数 %506 可以替换为常量（i32 96）
        Function: main, Block: Block200
            -> 操作数 %515 可以替换为常量（i32 99）
        Function: main, Block: Block201
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block201
            -> 操作数 %517 可以替换为常量（i32 99）
        Function: main, Block: Block201
            -> 操作数 %518 可以替换为常量（i32 1）
        Function: main, Block: Block202
            -> 操作数 %18 可以替换为常量（i32 200）
        Function: main, Block: Block202
            -> 操作数 %511 可以替换为常量（i32 97）
        Function: main, Block: Block202
            -> 操作数 %519 可以替换为常量（i32 99）
        Function: main, Block: Block204
            -> 操作数 %516 可以替换为常量（i32 98）
        Function: main, Block: Block204
            -> 操作数 %520 可以替换为常量（i32 99）
        Function: main, Block: Block205
            -> 操作数 %35 可以替换为常量（i32 0）
        Function: main, Block: Block205
            -> 操作数 %21 可以替换为常量（i32 99）
        Function: main, Block: Block205
            -> 操作数 %33 可以替换为常量（i32 99）
        Function: main, Block: Block205
            -> 操作数 %524 可以替换为常量（i32 100）
        Function: main, Block: Block206
            -> 操作数 %21 可以替换为常量（i32 99）
        Function: main, Block: Block206
            -> 操作数 %526 可以替换为常量（i32 1）
        Function: main, Block: Block207
            -> 操作数 %527 可以替换为常量（i32 65535）
    dead_branch:
        Function: main, Block: Block5
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block7
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block9
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block11
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block13
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block15
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block17
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block19
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block21
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block23
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block25
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block27
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block29
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block31
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block33
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block35
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block37
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block39
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block41
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block43
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block45
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block47
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block49
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block51
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block53
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block55
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block57
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block59
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block61
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block63
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block65
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block67
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block69
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block71
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block73
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block75
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block77
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block79
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block81
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block83
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block85
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block87
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block89
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block91
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block93
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block95
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block97
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block99
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block101
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block103
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block105
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block107
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block109
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block111
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block113
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block115
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block117
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block119
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block121
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block123
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block125
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block127
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block129
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block131
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block133
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block135
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block137
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block139
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block141
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block143
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block145
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block147
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block149
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block151
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block153
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block155
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block157
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block159
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block161
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block163
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block165
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block167
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block169
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block171
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block173
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block175
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block177
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block179
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block181
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block183
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block185
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block187
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block189
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block191
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block193
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block195
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block197
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block199
            -> 分支条件为常量（1），可以简化为无条件分支
        Function: main, Block: Block201
            -> 分支条件为常量（1），可以简化为无条件分支
    foldable_instruction:
        Function: main, Block: Block0
            -> %reg_4 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_6 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block0
            -> %reg_8 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block0
            -> %reg_11 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block1
            -> %reg_438 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block1
            -> %reg_13 = 指令结果为常量（i32 100）但未被折叠
        Function: main, Block: Block2
            -> %reg_15 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block2
            -> %reg_17 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block4
            -> %reg_541 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block5
            -> %reg_23 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block5
            -> %reg_24 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block6
            -> %reg_436 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block6
            -> %reg_437 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block7
            -> %reg_25 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block7
            -> %reg_27 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block7
            -> %reg_28 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block8
            -> %reg_542 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block8
            -> %reg_439 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block8
            -> %reg_419 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block8
            -> %reg_422 = 指令结果为常量（i32 0）但未被折叠
        Function: main, Block: Block9
            -> %reg_29 = 指令结果为常量（i32 2）但未被折叠
        Function: main, Block: Block9
            -> %reg_31 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block9
            -> %reg_32 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block10
            -> %reg_543 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block10
            -> %reg_441 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block11
            -> %reg_33 = 指令结果为常量（i32 3）但未被折叠
        Function: main, Block: Block11
            -> %reg_35 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block11
            -> %reg_36 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block12
            -> %reg_544 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block12
            -> %reg_442 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block13
            -> %reg_37 = 指令结果为常量（i32 4）但未被折叠
        Function: main, Block: Block13
            -> %reg_39 = 指令结果为常量（i32 5）但未被折叠
        Function: main, Block: Block13
            -> %reg_40 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block14
            -> %reg_545 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block14
            -> %reg_443 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block15
            -> %reg_41 = 指令结果为常量（i32 5）但未被折叠
        Function: main, Block: Block15
            -> %reg_43 = 指令结果为常量（i32 6）但未被折叠
        Function: main, Block: Block15
            -> %reg_44 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block16
            -> %reg_546 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block16
            -> %reg_444 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block17
            -> %reg_45 = 指令结果为常量（i32 6）但未被折叠
        Function: main, Block: Block17
            -> %reg_47 = 指令结果为常量（i32 7）但未被折叠
        Function: main, Block: Block17
            -> %reg_48 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block18
            -> %reg_547 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block18
            -> %reg_445 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block19
            -> %reg_49 = 指令结果为常量（i32 7）但未被折叠
        Function: main, Block: Block19
            -> %reg_51 = 指令结果为常量（i32 8）但未被折叠
        Function: main, Block: Block19
            -> %reg_52 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block20
            -> %reg_548 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block20
            -> %reg_446 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block21
            -> %reg_53 = 指令结果为常量（i32 8）但未被折叠
        Function: main, Block: Block21
            -> %reg_55 = 指令结果为常量（i32 9）但未被折叠
        Function: main, Block: Block21
            -> %reg_56 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block22
            -> %reg_549 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block22
            -> %reg_447 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block23
            -> %reg_57 = 指令结果为常量（i32 9）但未被折叠
        Function: main, Block: Block23
            -> %reg_59 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block23
            -> %reg_60 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block24
            -> %reg_550 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block24
            -> %reg_448 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block25
            -> %reg_61 = 指令结果为常量（i32 10）但未被折叠
        Function: main, Block: Block25
            -> %reg_63 = 指令结果为常量（i32 11）但未被折叠
        Function: main, Block: Block25
            -> %reg_64 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block26
            -> %reg_551 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block26
            -> %reg_449 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block27
            -> %reg_65 = 指令结果为常量（i32 11）但未被折叠
        Function: main, Block: Block27
            -> %reg_67 = 指令结果为常量（i32 12）但未被折叠
        Function: main, Block: Block27
            -> %reg_68 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block28
            -> %reg_552 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block28
            -> %reg_450 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block29
            -> %reg_69 = 指令结果为常量（i32 12）但未被折叠
        Function: main, Block: Block29
            -> %reg_71 = 指令结果为常量（i32 13）但未被折叠
        Function: main, Block: Block29
            -> %reg_72 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block30
            -> %reg_553 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block30
            -> %reg_451 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block31
            -> %reg_73 = 指令结果为常量（i32 13）但未被折叠
        Function: main, Block: Block31
            -> %reg_75 = 指令结果为常量（i32 14）但未被折叠
        Function: main, Block: Block31
            -> %reg_76 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block32
            -> %reg_554 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block32
            -> %reg_452 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block33
            -> %reg_77 = 指令结果为常量（i32 14）但未被折叠
        Function: main, Block: Block33
            -> %reg_79 = 指令结果为常量（i32 15）但未被折叠
        Function: main, Block: Block33
            -> %reg_80 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block34
            -> %reg_555 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block34
            -> %reg_453 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block35
            -> %reg_81 = 指令结果为常量（i32 15）但未被折叠
        Function: main, Block: Block35
            -> %reg_83 = 指令结果为常量（i32 16）但未被折叠
        Function: main, Block: Block35
            -> %reg_84 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block36
            -> %reg_556 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block36
            -> %reg_454 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block37
            -> %reg_85 = 指令结果为常量（i32 16）但未被折叠
        Function: main, Block: Block37
            -> %reg_87 = 指令结果为常量（i32 17）但未被折叠
        Function: main, Block: Block37
            -> %reg_88 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block38
            -> %reg_557 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block38
            -> %reg_455 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block39
            -> %reg_89 = 指令结果为常量（i32 17）但未被折叠
        Function: main, Block: Block39
            -> %reg_91 = 指令结果为常量（i32 18）但未被折叠
        Function: main, Block: Block39
            -> %reg_92 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block40
            -> %reg_558 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block40
            -> %reg_456 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block41
            -> %reg_93 = 指令结果为常量（i32 18）但未被折叠
        Function: main, Block: Block41
            -> %reg_95 = 指令结果为常量（i32 19）但未被折叠
        Function: main, Block: Block41
            -> %reg_96 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block42
            -> %reg_559 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block42
            -> %reg_457 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block43
            -> %reg_97 = 指令结果为常量（i32 19）但未被折叠
        Function: main, Block: Block43
            -> %reg_99 = 指令结果为常量（i32 20）但未被折叠
        Function: main, Block: Block43
            -> %reg_100 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block44
            -> %reg_560 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block44
            -> %reg_458 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block45
            -> %reg_101 = 指令结果为常量（i32 20）但未被折叠
        Function: main, Block: Block45
            -> %reg_103 = 指令结果为常量（i32 21）但未被折叠
        Function: main, Block: Block45
            -> %reg_104 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block46
            -> %reg_561 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block46
            -> %reg_459 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block47
            -> %reg_105 = 指令结果为常量（i32 21）但未被折叠
        Function: main, Block: Block47
            -> %reg_107 = 指令结果为常量（i32 22）但未被折叠
        Function: main, Block: Block47
            -> %reg_108 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block48
            -> %reg_562 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block48
            -> %reg_460 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block49
            -> %reg_109 = 指令结果为常量（i32 22）但未被折叠
        Function: main, Block: Block49
            -> %reg_111 = 指令结果为常量（i32 23）但未被折叠
        Function: main, Block: Block49
            -> %reg_112 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block50
            -> %reg_563 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block50
            -> %reg_461 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block51
            -> %reg_113 = 指令结果为常量（i32 23）但未被折叠
        Function: main, Block: Block51
            -> %reg_115 = 指令结果为常量（i32 24）但未被折叠
        Function: main, Block: Block51
            -> %reg_116 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block52
            -> %reg_564 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block52
            -> %reg_462 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block53
            -> %reg_117 = 指令结果为常量（i32 24）但未被折叠
        Function: main, Block: Block53
            -> %reg_119 = 指令结果为常量（i32 25）但未被折叠
        Function: main, Block: Block53
            -> %reg_120 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block54
            -> %reg_565 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block54
            -> %reg_463 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block55
            -> %reg_121 = 指令结果为常量（i32 25）但未被折叠
        Function: main, Block: Block55
            -> %reg_123 = 指令结果为常量（i32 26）但未被折叠
        Function: main, Block: Block55
            -> %reg_124 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block56
            -> %reg_566 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block56
            -> %reg_464 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block57
            -> %reg_125 = 指令结果为常量（i32 26）但未被折叠
        Function: main, Block: Block57
            -> %reg_127 = 指令结果为常量（i32 27）但未被折叠
        Function: main, Block: Block57
            -> %reg_128 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block58
            -> %reg_567 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block58
            -> %reg_465 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block59
            -> %reg_129 = 指令结果为常量（i32 27）但未被折叠
        Function: main, Block: Block59
            -> %reg_131 = 指令结果为常量（i32 28）但未被折叠
        Function: main, Block: Block59
            -> %reg_132 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block60
            -> %reg_568 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block60
            -> %reg_466 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block61
            -> %reg_133 = 指令结果为常量（i32 28）但未被折叠
        Function: main, Block: Block61
            -> %reg_135 = 指令结果为常量（i32 29）但未被折叠
        Function: main, Block: Block61
            -> %reg_136 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block62
            -> %reg_569 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block62
            -> %reg_467 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block63
            -> %reg_137 = 指令结果为常量（i32 29）但未被折叠
        Function: main, Block: Block63
            -> %reg_139 = 指令结果为常量（i32 30）但未被折叠
        Function: main, Block: Block63
            -> %reg_140 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block64
            -> %reg_570 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block64
            -> %reg_468 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block65
            -> %reg_141 = 指令结果为常量（i32 30）但未被折叠
        Function: main, Block: Block65
            -> %reg_143 = 指令结果为常量（i32 31）但未被折叠
        Function: main, Block: Block65
            -> %reg_144 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block66
            -> %reg_571 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block66
            -> %reg_469 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block67
            -> %reg_145 = 指令结果为常量（i32 31）但未被折叠
        Function: main, Block: Block67
            -> %reg_147 = 指令结果为常量（i32 32）但未被折叠
        Function: main, Block: Block67
            -> %reg_148 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block68
            -> %reg_572 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block68
            -> %reg_470 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block69
            -> %reg_149 = 指令结果为常量（i32 32）但未被折叠
        Function: main, Block: Block69
            -> %reg_151 = 指令结果为常量（i32 33）但未被折叠
        Function: main, Block: Block69
            -> %reg_152 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block70
            -> %reg_573 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block70
            -> %reg_471 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block71
            -> %reg_153 = 指令结果为常量（i32 33）但未被折叠
        Function: main, Block: Block71
            -> %reg_155 = 指令结果为常量（i32 34）但未被折叠
        Function: main, Block: Block71
            -> %reg_156 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block72
            -> %reg_574 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block72
            -> %reg_472 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block73
            -> %reg_157 = 指令结果为常量（i32 34）但未被折叠
        Function: main, Block: Block73
            -> %reg_159 = 指令结果为常量（i32 35）但未被折叠
        Function: main, Block: Block73
            -> %reg_160 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block74
            -> %reg_575 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block74
            -> %reg_473 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block75
            -> %reg_161 = 指令结果为常量（i32 35）但未被折叠
        Function: main, Block: Block75
            -> %reg_163 = 指令结果为常量（i32 36）但未被折叠
        Function: main, Block: Block75
            -> %reg_164 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block76
            -> %reg_576 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block76
            -> %reg_474 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block77
            -> %reg_165 = 指令结果为常量（i32 36）但未被折叠
        Function: main, Block: Block77
            -> %reg_167 = 指令结果为常量（i32 37）但未被折叠
        Function: main, Block: Block77
            -> %reg_168 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block78
            -> %reg_577 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block78
            -> %reg_475 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block79
            -> %reg_169 = 指令结果为常量（i32 37）但未被折叠
        Function: main, Block: Block79
            -> %reg_171 = 指令结果为常量（i32 38）但未被折叠
        Function: main, Block: Block79
            -> %reg_172 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block80
            -> %reg_578 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block80
            -> %reg_476 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block81
            -> %reg_173 = 指令结果为常量（i32 38）但未被折叠
        Function: main, Block: Block81
            -> %reg_175 = 指令结果为常量（i32 39）但未被折叠
        Function: main, Block: Block81
            -> %reg_176 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block82
            -> %reg_579 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block82
            -> %reg_477 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block83
            -> %reg_177 = 指令结果为常量（i32 39）但未被折叠
        Function: main, Block: Block83
            -> %reg_179 = 指令结果为常量（i32 40）但未被折叠
        Function: main, Block: Block83
            -> %reg_180 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block84
            -> %reg_580 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block84
            -> %reg_478 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block85
            -> %reg_181 = 指令结果为常量（i32 40）但未被折叠
        Function: main, Block: Block85
            -> %reg_183 = 指令结果为常量（i32 41）但未被折叠
        Function: main, Block: Block85
            -> %reg_184 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block86
            -> %reg_581 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block86
            -> %reg_479 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block87
            -> %reg_185 = 指令结果为常量（i32 41）但未被折叠
        Function: main, Block: Block87
            -> %reg_187 = 指令结果为常量（i32 42）但未被折叠
        Function: main, Block: Block87
            -> %reg_188 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block88
            -> %reg_582 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block88
            -> %reg_480 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block89
            -> %reg_189 = 指令结果为常量（i32 42）但未被折叠
        Function: main, Block: Block89
            -> %reg_191 = 指令结果为常量（i32 43）但未被折叠
        Function: main, Block: Block89
            -> %reg_192 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block90
            -> %reg_583 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block90
            -> %reg_481 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block91
            -> %reg_193 = 指令结果为常量（i32 43）但未被折叠
        Function: main, Block: Block91
            -> %reg_195 = 指令结果为常量（i32 44）但未被折叠
        Function: main, Block: Block91
            -> %reg_196 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block92
            -> %reg_584 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block92
            -> %reg_482 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block93
            -> %reg_197 = 指令结果为常量（i32 44）但未被折叠
        Function: main, Block: Block93
            -> %reg_199 = 指令结果为常量（i32 45）但未被折叠
        Function: main, Block: Block93
            -> %reg_200 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block94
            -> %reg_585 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block94
            -> %reg_483 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block95
            -> %reg_201 = 指令结果为常量（i32 45）但未被折叠
        Function: main, Block: Block95
            -> %reg_203 = 指令结果为常量（i32 46）但未被折叠
        Function: main, Block: Block95
            -> %reg_204 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block96
            -> %reg_586 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block96
            -> %reg_484 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block97
            -> %reg_205 = 指令结果为常量（i32 46）但未被折叠
        Function: main, Block: Block97
            -> %reg_207 = 指令结果为常量（i32 47）但未被折叠
        Function: main, Block: Block97
            -> %reg_208 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block98
            -> %reg_587 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block98
            -> %reg_485 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block99
            -> %reg_209 = 指令结果为常量（i32 47）但未被折叠
        Function: main, Block: Block99
            -> %reg_211 = 指令结果为常量（i32 48）但未被折叠
        Function: main, Block: Block99
            -> %reg_212 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block100
            -> %reg_588 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block100
            -> %reg_486 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block101
            -> %reg_213 = 指令结果为常量（i32 48）但未被折叠
        Function: main, Block: Block101
            -> %reg_215 = 指令结果为常量（i32 49）但未被折叠
        Function: main, Block: Block101
            -> %reg_216 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block102
            -> %reg_589 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block102
            -> %reg_487 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block103
            -> %reg_217 = 指令结果为常量（i32 49）但未被折叠
        Function: main, Block: Block103
            -> %reg_219 = 指令结果为常量（i32 50）但未被折叠
        Function: main, Block: Block103
            -> %reg_220 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block104
            -> %reg_590 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block104
            -> %reg_488 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block105
            -> %reg_221 = 指令结果为常量（i32 50）但未被折叠
        Function: main, Block: Block105
            -> %reg_223 = 指令结果为常量（i32 51）但未被折叠
        Function: main, Block: Block105
            -> %reg_224 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block106
            -> %reg_591 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block106
            -> %reg_489 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block107
            -> %reg_225 = 指令结果为常量（i32 51）但未被折叠
        Function: main, Block: Block107
            -> %reg_227 = 指令结果为常量（i32 52）但未被折叠
        Function: main, Block: Block107
            -> %reg_228 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block108
            -> %reg_592 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block108
            -> %reg_490 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block109
            -> %reg_229 = 指令结果为常量（i32 52）但未被折叠
        Function: main, Block: Block109
            -> %reg_231 = 指令结果为常量（i32 53）但未被折叠
        Function: main, Block: Block109
            -> %reg_232 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block110
            -> %reg_593 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block110
            -> %reg_491 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block111
            -> %reg_233 = 指令结果为常量（i32 53）但未被折叠
        Function: main, Block: Block111
            -> %reg_235 = 指令结果为常量（i32 54）但未被折叠
        Function: main, Block: Block111
            -> %reg_236 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block112
            -> %reg_594 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block112
            -> %reg_492 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block113
            -> %reg_237 = 指令结果为常量（i32 54）但未被折叠
        Function: main, Block: Block113
            -> %reg_239 = 指令结果为常量（i32 55）但未被折叠
        Function: main, Block: Block113
            -> %reg_240 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block114
            -> %reg_595 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block114
            -> %reg_493 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block115
            -> %reg_241 = 指令结果为常量（i32 55）但未被折叠
        Function: main, Block: Block115
            -> %reg_243 = 指令结果为常量（i32 56）但未被折叠
        Function: main, Block: Block115
            -> %reg_244 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block116
            -> %reg_596 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block116
            -> %reg_494 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block117
            -> %reg_245 = 指令结果为常量（i32 56）但未被折叠
        Function: main, Block: Block117
            -> %reg_247 = 指令结果为常量（i32 57）但未被折叠
        Function: main, Block: Block117
            -> %reg_248 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block118
            -> %reg_597 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block118
            -> %reg_495 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block119
            -> %reg_249 = 指令结果为常量（i32 57）但未被折叠
        Function: main, Block: Block119
            -> %reg_251 = 指令结果为常量（i32 58）但未被折叠
        Function: main, Block: Block119
            -> %reg_252 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block120
            -> %reg_598 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block120
            -> %reg_496 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block121
            -> %reg_253 = 指令结果为常量（i32 58）但未被折叠
        Function: main, Block: Block121
            -> %reg_255 = 指令结果为常量（i32 59）但未被折叠
        Function: main, Block: Block121
            -> %reg_256 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block122
            -> %reg_599 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block122
            -> %reg_497 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block123
            -> %reg_257 = 指令结果为常量（i32 59）但未被折叠
        Function: main, Block: Block123
            -> %reg_259 = 指令结果为常量（i32 60）但未被折叠
        Function: main, Block: Block123
            -> %reg_260 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block124
            -> %reg_600 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block124
            -> %reg_498 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block125
            -> %reg_261 = 指令结果为常量（i32 60）但未被折叠
        Function: main, Block: Block125
            -> %reg_263 = 指令结果为常量（i32 61）但未被折叠
        Function: main, Block: Block125
            -> %reg_264 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block126
            -> %reg_601 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block126
            -> %reg_499 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block127
            -> %reg_265 = 指令结果为常量（i32 61）但未被折叠
        Function: main, Block: Block127
            -> %reg_267 = 指令结果为常量（i32 62）但未被折叠
        Function: main, Block: Block127
            -> %reg_268 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block128
            -> %reg_602 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block128
            -> %reg_500 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block129
            -> %reg_269 = 指令结果为常量（i32 62）但未被折叠
        Function: main, Block: Block129
            -> %reg_271 = 指令结果为常量（i32 63）但未被折叠
        Function: main, Block: Block129
            -> %reg_272 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block130
            -> %reg_603 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block130
            -> %reg_501 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block131
            -> %reg_273 = 指令结果为常量（i32 63）但未被折叠
        Function: main, Block: Block131
            -> %reg_275 = 指令结果为常量（i32 64）但未被折叠
        Function: main, Block: Block131
            -> %reg_276 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block132
            -> %reg_604 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block132
            -> %reg_502 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block133
            -> %reg_277 = 指令结果为常量（i32 64）但未被折叠
        Function: main, Block: Block133
            -> %reg_279 = 指令结果为常量（i32 65）但未被折叠
        Function: main, Block: Block133
            -> %reg_280 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block134
            -> %reg_605 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block134
            -> %reg_503 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block135
            -> %reg_281 = 指令结果为常量（i32 65）但未被折叠
        Function: main, Block: Block135
            -> %reg_283 = 指令结果为常量（i32 66）但未被折叠
        Function: main, Block: Block135
            -> %reg_284 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block136
            -> %reg_606 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block136
            -> %reg_504 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block137
            -> %reg_285 = 指令结果为常量（i32 66）但未被折叠
        Function: main, Block: Block137
            -> %reg_287 = 指令结果为常量（i32 67）但未被折叠
        Function: main, Block: Block137
            -> %reg_288 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block138
            -> %reg_607 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block138
            -> %reg_505 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block139
            -> %reg_289 = 指令结果为常量（i32 67）但未被折叠
        Function: main, Block: Block139
            -> %reg_291 = 指令结果为常量（i32 68）但未被折叠
        Function: main, Block: Block139
            -> %reg_292 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block140
            -> %reg_608 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block140
            -> %reg_506 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block141
            -> %reg_293 = 指令结果为常量（i32 68）但未被折叠
        Function: main, Block: Block141
            -> %reg_295 = 指令结果为常量（i32 69）但未被折叠
        Function: main, Block: Block141
            -> %reg_296 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block142
            -> %reg_609 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block142
            -> %reg_507 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block143
            -> %reg_297 = 指令结果为常量（i32 69）但未被折叠
        Function: main, Block: Block143
            -> %reg_299 = 指令结果为常量（i32 70）但未被折叠
        Function: main, Block: Block143
            -> %reg_300 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block144
            -> %reg_610 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block144
            -> %reg_508 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block145
            -> %reg_301 = 指令结果为常量（i32 70）但未被折叠
        Function: main, Block: Block145
            -> %reg_303 = 指令结果为常量（i32 71）但未被折叠
        Function: main, Block: Block145
            -> %reg_304 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block146
            -> %reg_611 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block146
            -> %reg_509 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block147
            -> %reg_305 = 指令结果为常量（i32 71）但未被折叠
        Function: main, Block: Block147
            -> %reg_307 = 指令结果为常量（i32 72）但未被折叠
        Function: main, Block: Block147
            -> %reg_308 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block148
            -> %reg_612 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block148
            -> %reg_510 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block149
            -> %reg_309 = 指令结果为常量（i32 72）但未被折叠
        Function: main, Block: Block149
            -> %reg_311 = 指令结果为常量（i32 73）但未被折叠
        Function: main, Block: Block149
            -> %reg_312 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block150
            -> %reg_613 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block150
            -> %reg_511 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block151
            -> %reg_313 = 指令结果为常量（i32 73）但未被折叠
        Function: main, Block: Block151
            -> %reg_315 = 指令结果为常量（i32 74）但未被折叠
        Function: main, Block: Block151
            -> %reg_316 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block152
            -> %reg_614 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block152
            -> %reg_512 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block153
            -> %reg_317 = 指令结果为常量（i32 74）但未被折叠
        Function: main, Block: Block153
            -> %reg_319 = 指令结果为常量（i32 75）但未被折叠
        Function: main, Block: Block153
            -> %reg_320 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block154
            -> %reg_615 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block154
            -> %reg_513 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block155
            -> %reg_321 = 指令结果为常量（i32 75）但未被折叠
        Function: main, Block: Block155
            -> %reg_323 = 指令结果为常量（i32 76）但未被折叠
        Function: main, Block: Block155
            -> %reg_324 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block156
            -> %reg_616 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block156
            -> %reg_514 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block157
            -> %reg_325 = 指令结果为常量（i32 76）但未被折叠
        Function: main, Block: Block157
            -> %reg_327 = 指令结果为常量（i32 77）但未被折叠
        Function: main, Block: Block157
            -> %reg_328 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block158
            -> %reg_617 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block158
            -> %reg_515 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block159
            -> %reg_329 = 指令结果为常量（i32 77）但未被折叠
        Function: main, Block: Block159
            -> %reg_331 = 指令结果为常量（i32 78）但未被折叠
        Function: main, Block: Block159
            -> %reg_332 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block160
            -> %reg_618 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block160
            -> %reg_516 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block161
            -> %reg_333 = 指令结果为常量（i32 78）但未被折叠
        Function: main, Block: Block161
            -> %reg_335 = 指令结果为常量（i32 79）但未被折叠
        Function: main, Block: Block161
            -> %reg_336 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block162
            -> %reg_619 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block162
            -> %reg_517 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block163
            -> %reg_337 = 指令结果为常量（i32 79）但未被折叠
        Function: main, Block: Block163
            -> %reg_339 = 指令结果为常量（i32 80）但未被折叠
        Function: main, Block: Block163
            -> %reg_340 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block164
            -> %reg_620 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block164
            -> %reg_518 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block165
            -> %reg_341 = 指令结果为常量（i32 80）但未被折叠
        Function: main, Block: Block165
            -> %reg_343 = 指令结果为常量（i32 81）但未被折叠
        Function: main, Block: Block165
            -> %reg_344 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block166
            -> %reg_621 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block166
            -> %reg_519 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block167
            -> %reg_345 = 指令结果为常量（i32 81）但未被折叠
        Function: main, Block: Block167
            -> %reg_347 = 指令结果为常量（i32 82）但未被折叠
        Function: main, Block: Block167
            -> %reg_348 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block168
            -> %reg_622 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block168
            -> %reg_520 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block169
            -> %reg_349 = 指令结果为常量（i32 82）但未被折叠
        Function: main, Block: Block169
            -> %reg_351 = 指令结果为常量（i32 83）但未被折叠
        Function: main, Block: Block169
            -> %reg_352 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block170
            -> %reg_623 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block170
            -> %reg_521 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block171
            -> %reg_353 = 指令结果为常量（i32 83）但未被折叠
        Function: main, Block: Block171
            -> %reg_355 = 指令结果为常量（i32 84）但未被折叠
        Function: main, Block: Block171
            -> %reg_356 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block172
            -> %reg_624 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block172
            -> %reg_522 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block173
            -> %reg_357 = 指令结果为常量（i32 84）但未被折叠
        Function: main, Block: Block173
            -> %reg_359 = 指令结果为常量（i32 85）但未被折叠
        Function: main, Block: Block173
            -> %reg_360 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block174
            -> %reg_625 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block174
            -> %reg_523 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block175
            -> %reg_361 = 指令结果为常量（i32 85）但未被折叠
        Function: main, Block: Block175
            -> %reg_363 = 指令结果为常量（i32 86）但未被折叠
        Function: main, Block: Block175
            -> %reg_364 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block176
            -> %reg_626 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block176
            -> %reg_524 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block177
            -> %reg_365 = 指令结果为常量（i32 86）但未被折叠
        Function: main, Block: Block177
            -> %reg_367 = 指令结果为常量（i32 87）但未被折叠
        Function: main, Block: Block177
            -> %reg_368 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block178
            -> %reg_627 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block178
            -> %reg_525 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block179
            -> %reg_369 = 指令结果为常量（i32 87）但未被折叠
        Function: main, Block: Block179
            -> %reg_371 = 指令结果为常量（i32 88）但未被折叠
        Function: main, Block: Block179
            -> %reg_372 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block180
            -> %reg_628 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block180
            -> %reg_526 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block181
            -> %reg_373 = 指令结果为常量（i32 88）但未被折叠
        Function: main, Block: Block181
            -> %reg_375 = 指令结果为常量（i32 89）但未被折叠
        Function: main, Block: Block181
            -> %reg_376 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block182
            -> %reg_629 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block182
            -> %reg_527 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block183
            -> %reg_377 = 指令结果为常量（i32 89）但未被折叠
        Function: main, Block: Block183
            -> %reg_379 = 指令结果为常量（i32 90）但未被折叠
        Function: main, Block: Block183
            -> %reg_380 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block184
            -> %reg_630 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block184
            -> %reg_528 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block185
            -> %reg_381 = 指令结果为常量（i32 90）但未被折叠
        Function: main, Block: Block185
            -> %reg_383 = 指令结果为常量（i32 91）但未被折叠
        Function: main, Block: Block185
            -> %reg_384 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block186
            -> %reg_631 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block186
            -> %reg_529 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block187
            -> %reg_385 = 指令结果为常量（i32 91）但未被折叠
        Function: main, Block: Block187
            -> %reg_387 = 指令结果为常量（i32 92）但未被折叠
        Function: main, Block: Block187
            -> %reg_388 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block188
            -> %reg_632 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block188
            -> %reg_530 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block189
            -> %reg_389 = 指令结果为常量（i32 92）但未被折叠
        Function: main, Block: Block189
            -> %reg_391 = 指令结果为常量（i32 93）但未被折叠
        Function: main, Block: Block189
            -> %reg_392 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block190
            -> %reg_633 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block190
            -> %reg_531 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block191
            -> %reg_393 = 指令结果为常量（i32 93）但未被折叠
        Function: main, Block: Block191
            -> %reg_395 = 指令结果为常量（i32 94）但未被折叠
        Function: main, Block: Block191
            -> %reg_396 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block192
            -> %reg_634 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block192
            -> %reg_532 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block193
            -> %reg_397 = 指令结果为常量（i32 94）但未被折叠
        Function: main, Block: Block193
            -> %reg_399 = 指令结果为常量（i32 95）但未被折叠
        Function: main, Block: Block193
            -> %reg_400 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block194
            -> %reg_635 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block194
            -> %reg_533 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block195
            -> %reg_401 = 指令结果为常量（i32 95）但未被折叠
        Function: main, Block: Block195
            -> %reg_403 = 指令结果为常量（i32 96）但未被折叠
        Function: main, Block: Block195
            -> %reg_404 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block196
            -> %reg_636 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block196
            -> %reg_534 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block197
            -> %reg_405 = 指令结果为常量（i32 96）但未被折叠
        Function: main, Block: Block197
            -> %reg_407 = 指令结果为常量（i32 97）但未被折叠
        Function: main, Block: Block197
            -> %reg_408 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block198
            -> %reg_637 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block198
            -> %reg_535 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block199
            -> %reg_409 = 指令结果为常量（i32 97）但未被折叠
        Function: main, Block: Block199
            -> %reg_411 = 指令结果为常量（i32 98）但未被折叠
        Function: main, Block: Block199
            -> %reg_412 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block200
            -> %reg_638 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block200
            -> %reg_536 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block201
            -> %reg_413 = 指令结果为常量（i32 98）但未被折叠
        Function: main, Block: Block201
            -> %reg_415 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block201
            -> %reg_416 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block202
            -> %reg_639 = 指令结果为常量（i32 200）但未被折叠
        Function: main, Block: Block202
            -> %reg_537 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block203
            -> %reg_417 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block204
            -> %reg_538 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block205
            -> %reg_539 = 指令结果为常量（i32 99）但未被折叠
        Function: main, Block: Block205
            -> %reg_424 = 指令结果为常量（i32 100）但未被折叠
        Function: main, Block: Block206
            -> %reg_430 = 指令结果为常量（i32 1）但未被折叠
        Function: main, Block: Block207
            -> %reg_433 = 指令结果为常量（i32 65535）但未被折叠
