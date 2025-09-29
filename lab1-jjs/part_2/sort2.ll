;从运行时库中调用输入输出外部函数的声明
declare i32 @getint()
declare void @putint(i32)
declare void @putch(i32)

;全局变量的声明及初始化
@arr = global [100 x i32] zeroinitializer
@n = global i32 0

define void @sort(i32 %n) {
entry:  ;LLVM IR的基本块标签，实现逻辑的跳转和循环的运行等功能
  %i = alloca i32
  %j = alloca i32
  %tmp = alloca i32
  store i32 0, i32* %i ;赋值操作
  br label %while_i ;通过br label进入循环体

while_i: ; 循环判断
  %i_val = load i32, i32* %i ;读取操作
  %n_minus1 = sub i32 %n, 1
  %cond_i = icmp slt i32 %i_val, %n_minus1 ;比较操作
  br i1 %cond_i, label %while_i_body, label %while_i_end ;%cond_i为真执行循环体,否则跳转至结束

while_i_body:
  store i32 0, i32* %j
  br label %while_j

while_j: ; 内层循环
  %j_val = load i32, i32* %j
  %i_val2 = load i32, i32* %i
  %n_minus1_2 = sub i32 %n, 1
  %limit = sub i32 %n_minus1_2, %i_val2
  %cond_j = icmp slt i32 %j_val, %limit
  br i1 %cond_j, label %while_j_body, label %while_j_end

while_j_body:
  %idx1 = getelementptr [100 x i32], [100 x i32]* @arr, i32 0, i32 %j_val
  %a = load i32, i32* %idx1 ;通过GEP计算对应下标的指针地址并读取
  %j_next = add i32 %j_val, 1
  %idx2 = getelementptr [100 x i32], [100 x i32]* @arr, i32 0, i32 %j_next
  %b = load i32, i32* %idx2
  %cmp = icmp sgt i32 %a, %b
  br i1 %cmp, label %swap, label %noswap

swap: ;与c不同 直接交换即可
  store i32 %b, i32* %idx1
  store i32 %a, i32* %idx2
  br label %noswap

noswap: ;无论是否交换都会跳转至此处实现循环体增量
  %j_inc = add i32 %j_val, 1
  store i32 %j_inc, i32* %j
  br label %while_j

while_j_end:
  %i_inc = add i32 %i_val2, 1
  store i32 %i_inc, i32* %i
  br label %while_i

while_i_end:
  ret void
}

define i32 @main() {
entry:
  %i = alloca i32
  %result = alloca i32

  ; 读取n
  %nval = call i32 @getint()
  store i32 %nval, i32* @n
  store i32 0, i32* %i
  br label %while_read

while_read:
  %i_val = load i32, i32* %i
  %nval2 = load i32, i32* @n
  %cond = icmp slt i32 %i_val, %nval2
  br i1 %cond, label %read_body, label %read_end

read_body:
  %x = call i32 @getint()
  %idx = getelementptr [100 x i32], [100 x i32]* @arr, i32 0, i32 %i_val
  store i32 %x, i32* %idx
  %i_next = add i32 %i_val, 1
  store i32 %i_next, i32* %i
  br label %while_read

read_end:
  %nval3 = load i32, i32* @n
  call void @sort(i32 %nval3) ; 函数调用

  ; 结果计算,存储值result
  %first = getelementptr [100 x i32], [100 x i32]* @arr, i32 0, i32 0
  %min = load i32, i32* %first
  %nval4 = load i32, i32* @n
  %last_idx = sub i32 %nval4, 1
  %last = getelementptr [100 x i32], [100 x i32]* @arr, i32 0, i32 %last_idx
  %max = load i32, i32* %last
  %sum = add i32 %min, %max
  store i32 %sum, i32* %result

  %r = load i32, i32* %result
  call void @putint(i32 %r)
  call void @putch(i32 10); 输出换行

  ret i32 0
}
