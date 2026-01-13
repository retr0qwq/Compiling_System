; Function Declarations
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

; Global Variable Declarations


; Function Definitions
define i32 @main()
{
Block0:
	%reg_1 = add i32 1, 0
	%reg_2 = sub i32 0, %reg_1
	%reg_3 = icmp eq i32 %reg_2, 0
	%reg_4 = zext i1 %reg_3 to i32
	%reg_5 = icmp eq i32 %reg_4, 0
	%reg_6 = zext i1 %reg_5 to i32
	%reg_7 = icmp eq i32 %reg_6, 0
	%reg_8 = zext i1 %reg_7 to i32
	%reg_9 = icmp eq i32 %reg_8, 0
	%reg_10 = zext i1 %reg_9 to i32
	%reg_11 = icmp eq i32 %reg_10, 0
	%reg_12 = zext i1 %reg_11 to i32
	%reg_13 = sub i32 0, %reg_12
	call void @putint(i32 %reg_13)
	%reg_14 = add i32 10, 0
	call void @putch(i32 %reg_14)
	%reg_15 = add i32 1, 0
	%reg_16 = sub i32 0, %reg_15
	%reg_17 = icmp eq i32 %reg_16, 0
	%reg_18 = zext i1 %reg_17 to i32
	%reg_19 = icmp eq i32 %reg_18, 0
	%reg_20 = zext i1 %reg_19 to i32
	call void @putint(i32 %reg_20)
	%reg_21 = add i32 10, 0
	call void @putch(i32 %reg_21)
	%reg_22 = add i32 0, 0
	ret i32 %reg_22
}
