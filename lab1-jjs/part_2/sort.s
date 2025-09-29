	.text
	.globl main
	.attribute	4, 16
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0"

sort:
.sort_0:
	sd			s1, -16(sp)
	sd			ra, -8(sp)
	addi		sp, sp, -32
	add			a0, x0, a0
	sw			a0, 12(sp)
	jal			x0, .sort_1
.sort_1:
	addiw		t0, x0, 0
	sw			t0, 8(sp)
	addiw		t0, x0, 0
	sw			t0, 4(sp)
	addiw		t0, x0, 0
	sw			t0, 0(sp)
	addiw		t0, x0, 0
	sw			t0, 8(sp)
	jal			x0, .sort_2
.sort_2:
	lw			s1, 8(sp)
	lw			t2, 12(sp)
	addiw		t1, x0, 1
	subw		t0, t2, t1
	blt			s1, t0, .sort_3
	jal			x0, .sort_4
.sort_3:
	addiw		t0, x0, 0
	sw			t0, 4(sp)
	jal			x0, .sort_5
.sort_4:
	addi		sp, sp, 32
	ld			ra, -8(sp)
	ld			s1, -16(sp)
	jalr		x0, ra, 0
.sort_5:
	lw			s1, 4(sp)
	lw			t2, 12(sp)
	addiw		t1, x0, 1
	subw		t0, t2, t1
	lw			t1, 8(sp)
	subw		t0, t0, t1
	blt			s1, t0, .sort_6
	jal			x0, .sort_7
.sort_6:
	lw			t2, 4(sp)
	add			t2, x0, t2
	la			t0, arr
	slli		t1, t2, 2
	add			t0, t0, t1
	lw			s1, 0(t0)
	lw			t2, 4(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	add			t0, x0, t0
	la			t1, arr
	slli		t0, t0, 2
	add			t1, t1, t0
	lw			t0, 0(t1)
	bgt			s1, t0, .sort_8
	jal			x0, .sort_9
.sort_7:
	lw			t2, 8(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	sw			t0, 8(sp)
	jal			x0, .sort_2
.sort_8:
	lw			t2, 4(sp)
	add			t2, x0, t2
	la			t1, arr
	slli		t0, t2, 2
	add			t1, t1, t0
	lw			t0, 0(t1)
	sw			t0, 0(sp)
	lw			t2, 4(sp)
	add			t2, x0, t2
	la			t1, arr
	slli		t0, t2, 2
	add			s1, t1, t0
	lw			t2, 4(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	add			t0, x0, t0
	la			t1, arr
	slli		t0, t0, 2
	add			t1, t1, t0
	lw			t0, 0(t1)
	sw			t0, 0(s1)
	lw			t2, 4(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	add			t0, x0, t0
	la			t1, arr
	slli		t0, t0, 2
	add			t1, t1, t0
	lw			t0, 0(sp)
	sw			t0, 0(t1)
	jal			x0, .sort_9
.sort_9:
	lw			t2, 4(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	sw			t0, 4(sp)
	jal			x0, .sort_5
main:
.main_0:
	sd			s1, -16(sp)
	sd			ra, -8(sp)
	addi		sp, sp, -24
	jal			x0, .main_1
.main_1:
	addiw		t0, x0, 0
	sw			t0, 4(sp)
	addiw		t0, x0, 0
	sw			t0, 0(sp)
	call		getint
	add			t1, x0, a0
	la			t0, n
	sw			t1, 0(t0)
	addiw		t0, x0, 0
	sw			t0, 4(sp)
	jal			x0, .main_2
.main_2:
	lw			t2, 4(sp)
	la			t1, n
	lw			t0, 0(t1)
	blt			t2, t0, .main_3
	jal			x0, .main_4
.main_3:
	lw			t2, 4(sp)
	add			t2, x0, t2
	la			t1, arr
	slli		t0, t2, 2
	add			s1, t1, t0
	call		getint
	add			t0, x0, a0
	sw			t0, 0(s1)
	lw			t2, 4(sp)
	addiw		t1, x0, 1
	addw		t0, t2, t1
	sw			t0, 4(sp)
	jal			x0, .main_2
.main_4:
	la			t0, n
	lw			a0, 0(t0)
	add			a0, x0, a0
	call		sort
	addiw		t1, x0, 0
	add			t1, x0, t1
	la			t0, arr
	slli		t1, t1, 2
	add			t0, t0, t1
	lw			s1, 0(t0)
	la			t0, n
	lw			t2, 0(t0)
	addiw		t0, x0, 1
	subw		t1, t2, t0
	add			t1, x0, t1
	la			t0, arr
	slli		t1, t1, 2
	add			t0, t0, t1
	lw			t1, 0(t0)
	addw		t0, s1, t1
	sw			t0, 0(sp)
	lw			a0, 0(sp)
	add			a0, x0, a0
	call		putint
	addiw		a0, x0, 10
	add			a0, x0, a0
	call		putch
	addiw		a0, x0, 0
	add			a0, x0, a0
	addi		sp, sp, 24
	ld			ra, -8(sp)
	ld			s1, -16(sp)
	jalr		x0, ra, 0
	.data
n:
	.word	0
arr:
	.zero	1600
