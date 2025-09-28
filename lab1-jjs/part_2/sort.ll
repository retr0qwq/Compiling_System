declare i32 @getint()
declare i32 @getch()
declare i32 @getarray(ptr)
declare float @getfloat()
declare i32 @getfarray(ptr)
declare void @putint(i32)
declare void @putch(i32)
declare void @putarray(i32, ptr)
declare void @putfloat(float)
declare void @putfarray(i32, ptr)
declare void @_sysy_starttime(i32)
declare void @_sysy_stoptime(i32)
declare void @llvm.memset.p0.i32(ptr, i8, i32, i1)
declare void @lsccll.lib.memset_i8(ptr, i8, i32)
declare void @lsccll.lib.memset_i32(ptr, i32, i32)
declare void @lsccll.lib.parallel.loop(ptr, i32, i32, i32, i32, ...)

@n = global i32 zeroinitializer
@arr = global [100 x i32] zeroinitializer

define void @sort(i32 %reg_0)
{
Block0: ; Func define at line 4
	%reg_6 = alloca i32
	%reg_4 = alloca i32
	%reg_2 = alloca i32
	%reg_1 = alloca i32
	store i32 %reg_0, ptr %reg_1
	br label %Block1
Block1: ; Func body at line 4
	%reg_3 = add i32 0, 0
	store i32 %reg_3, ptr %reg_2
	%reg_5 = add i32 0, 0
	store i32 %reg_5, ptr %reg_4
	%reg_7 = add i32 0, 0
	store i32 %reg_7, ptr %reg_6
	%reg_8 = add i32 0, 0
	store i32 %reg_8, ptr %reg_2
	br label %Block2
Block2: ; While condition at line 7
	%reg_9 = load i32, ptr %reg_2
	%reg_10 = load i32, ptr %reg_1
	%reg_11 = add i32 1, 0
	%reg_12 = sub i32 %reg_10, %reg_11
	%reg_13 = icmp slt i32 %reg_9, %reg_12
	br i1 %reg_13, label %Block3, label %Block4
Block3: ; While body at line 7
	%reg_14 = add i32 0, 0
	store i32 %reg_14, ptr %reg_4
	br label %Block5
Block4: ; While end at line 7
	ret void
Block5: ; While condition at line 9
	%reg_15 = load i32, ptr %reg_4
	%reg_16 = load i32, ptr %reg_1
	%reg_17 = add i32 1, 0
	%reg_18 = sub i32 %reg_16, %reg_17
	%reg_19 = load i32, ptr %reg_2
	%reg_20 = sub i32 %reg_18, %reg_19
	%reg_21 = icmp slt i32 %reg_15, %reg_20
	br i1 %reg_21, label %Block6, label %Block7
Block6: ; While body at line 9
	%reg_22 = load i32, ptr %reg_4
	%reg_23 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_22
	%reg_24 = load i32, ptr %reg_23
	%reg_25 = load i32, ptr %reg_4
	%reg_26 = add i32 1, 0
	%reg_27 = add i32 %reg_25, %reg_26
	%reg_28 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_27
	%reg_29 = load i32, ptr %reg_28
	%reg_30 = icmp sgt i32 %reg_24, %reg_29
	br i1 %reg_30, label %Block8, label %Block9
Block7: ; While end at line 9
	%reg_49 = load i32, ptr %reg_2
	%reg_50 = add i32 1, 0
	%reg_51 = add i32 %reg_49, %reg_50
	store i32 %reg_51, ptr %reg_2
	br label %Block2
Block8: ; If then at line 10
	%reg_31 = load i32, ptr %reg_4
	%reg_32 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_31
	%reg_33 = load i32, ptr %reg_32
	store i32 %reg_33, ptr %reg_6
	%reg_34 = load i32, ptr %reg_4
	%reg_35 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_34
	%reg_36 = load i32, ptr %reg_4
	%reg_37 = add i32 1, 0
	%reg_38 = add i32 %reg_36, %reg_37
	%reg_39 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_38
	%reg_40 = load i32, ptr %reg_39
	store i32 %reg_40, ptr %reg_35
	%reg_41 = load i32, ptr %reg_4
	%reg_42 = add i32 1, 0
	%reg_43 = add i32 %reg_41, %reg_42
	%reg_44 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_43
	%reg_45 = load i32, ptr %reg_6
	store i32 %reg_45, ptr %reg_44
	br label %Block9
Block9: ; If end at line 10
	%reg_46 = load i32, ptr %reg_4
	%reg_47 = add i32 1, 0
	%reg_48 = add i32 %reg_46, %reg_47
	store i32 %reg_48, ptr %reg_4
	br label %Block5
}

define i32 @main()
{
Block0: ; Func define at line 21
	%reg_2 = alloca i32
	%reg_0 = alloca i32
	br label %Block1
Block1: ; Func body at line 21
	%reg_1 = add i32 0, 0
	store i32 %reg_1, ptr %reg_0
	%reg_3 = add i32 0, 0
	store i32 %reg_3, ptr %reg_2
	%reg_4 = call i32 @getint()
	store i32 %reg_4, ptr @n
	%reg_5 = add i32 0, 0
	store i32 %reg_5, ptr %reg_0
	br label %Block2
Block2: ; While condition at line 25
	%reg_6 = load i32, ptr %reg_0
	%reg_7 = load i32, ptr @n
	%reg_8 = icmp slt i32 %reg_6, %reg_7
	br i1 %reg_8, label %Block3, label %Block4
Block3: ; While body at line 25
	%reg_9 = load i32, ptr %reg_0
	%reg_10 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_9
	%reg_11 = call i32 @getint()
	store i32 %reg_11, ptr %reg_10
	%reg_12 = load i32, ptr %reg_0
	%reg_13 = add i32 1, 0
	%reg_14 = add i32 %reg_12, %reg_13
	store i32 %reg_14, ptr %reg_0
	br label %Block2
Block4: ; While end at line 25
	%reg_15 = load i32, ptr @n
	call void @sort(i32 %reg_15)
	%reg_16 = add i32 0, 0
	%reg_17 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_16
	%reg_18 = load i32, ptr %reg_17
	%reg_19 = load i32, ptr @n
	%reg_20 = add i32 1, 0
	%reg_21 = sub i32 %reg_19, %reg_20
	%reg_22 = getelementptr [100 x i32], ptr @arr, i32 0, i32 %reg_21
	%reg_23 = load i32, ptr %reg_22
	%reg_24 = add i32 %reg_18, %reg_23
	store i32 %reg_24, ptr %reg_2
	%reg_25 = load i32, ptr %reg_2
	call void @putint(i32 %reg_25)
	%reg_26 = add i32 10, 0
	call void @putch(i32 %reg_26)
	%reg_27 = add i32 0, 0
	ret i32 %reg_27
}
