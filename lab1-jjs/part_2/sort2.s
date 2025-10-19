	.text
	.file	"sort2.ll"
	.globl	sort                            # -- Begin function sort
	.p2align	4, 0x90
	.type	sort,@function
sort:                                   # @sort
	.cfi_startproc
# %bb.0:                                # %entry
                                        # kill: def $edi killed $edi def $rdi
	movl	$0, -12(%rsp)
	leal	-1(%rdi), %r8d
	movq	arr@GOTPCREL(%rip), %r9
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_7:                                # %while_j_end
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%esi
	movl	%esi, -12(%rsp)
.LBB0_1:                                # %while_i
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	cmpl	%r8d, -12(%rsp)
	jge	.LBB0_8
# %bb.2:                                # %while_i_body
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$0, -8(%rsp)
	jmp	.LBB0_3
	.p2align	4, 0x90
.LBB0_6:                                # %noswap
                                        #   in Loop: Header=BB0_3 Depth=2
	movl	%edx, -8(%rsp)
.LBB0_3:                                # %while_j
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-8(%rsp), %edx
	movl	-12(%rsp), %esi
	movl	%esi, %eax
	notl	%eax
	addl	%edi, %eax
	cmpl	%eax, %edx
	jge	.LBB0_7
# %bb.4:                                # %while_j_body
                                        #   in Loop: Header=BB0_3 Depth=2
	movslq	%edx, %rax
	movl	(%r9,%rax,4), %r10d
	incl	%edx
	movslq	%edx, %rsi
	movl	(%r9,%rsi,4), %ecx
	cmpl	%ecx, %r10d
	jle	.LBB0_6
# %bb.5:                                # %swap
                                        #   in Loop: Header=BB0_3 Depth=2
	leaq	(%r9,%rax,4), %rax
	leaq	(%r9,%rsi,4), %rsi
	movl	%ecx, (%rax)
	movl	%r10d, (%rsi)
	jmp	.LBB0_6
.LBB0_8:                                # %while_i_end
	retq
.Lfunc_end0:
	.size	sort, .Lfunc_end0-sort
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %rbp, -16
	callq	getint@PLT
	movq	n@GOTPCREL(%rip), %rbx
	movl	%eax, (%rbx)
	movl	$0, 8(%rsp)
	movq	arr@GOTPCREL(%rip), %r14
	.p2align	4, 0x90
.LBB1_1:                                # %while_read
                                        # =>This Inner Loop Header: Depth=1
	movl	8(%rsp), %ebp
	cmpl	(%rbx), %ebp
	jge	.LBB1_3
# %bb.2:                                # %read_body
                                        #   in Loop: Header=BB1_1 Depth=1
	callq	getint@PLT
	movslq	%ebp, %rcx
	movl	%eax, (%r14,%rcx,4)
	incl	%ebp
	movl	%ebp, 8(%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %read_end
	movl	(%rbx), %edi
	callq	sort@PLT
	movl	(%r14), %edi
	movl	(%rbx), %eax
	decl	%eax
	cltq
	addl	(%r14,%rax,4), %edi
	movl	%edi, 12(%rsp)
	callq	putint@PLT
	movl	$10, %edi
	callq	putch@PLT
	xorl	%eax, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	arr,@object                     # @arr
	.bss
	.globl	arr
	.p2align	4
arr:
	.zero	400
	.size	arr, 400

	.type	n,@object                       # @n
	.globl	n
	.p2align	2
n:
	.long	0                               # 0x0
	.size	n, 4

	.section	".note.GNU-stack","",@progbits
