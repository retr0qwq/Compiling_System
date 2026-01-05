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
	%reg_2 = add i32 1000000, 0
	%reg_4 = add i32 0, 0
	%reg_6 = add i32 0, 0
	%reg_8 = add i32 0, 0
	br label %Block1
Block1:
	%reg_140 = phi i32 [ %reg_140, %Block5 ], [ %reg_2, %Block0 ]
	%reg_130 = phi i32 [ %reg_102, %Block5 ], [ %reg_4, %Block0 ]
	%reg_120 = phi i32 [ %reg_119, %Block5 ], [ %reg_6, %Block0 ]
	%reg_115 = phi i32 [ %reg_114, %Block5 ], [ %reg_8, %Block0 ]
	%reg_11 = icmp slt i32 %reg_130, %reg_140
	br i1 %reg_11, label %Block2, label %Block3
Block2:
	%reg_13 = add i32 10, 0
	%reg_14 = srem i32 %reg_130, %reg_13
	%reg_15 = add i32 0, 0
	%reg_16 = icmp eq i32 %reg_14, %reg_15
	br i1 %reg_16, label %Block4, label %Block6
Block3:
	call void @putint(i32 %reg_120)
	%reg_104 = add i32 10, 0
	call void @putch(i32 %reg_104)
	call void @putint(i32 %reg_115)
	%reg_106 = add i32 10, 0
	call void @putch(i32 %reg_106)
	%reg_107 = add i32 0, 0
	ret i32 %reg_107
Block4:
	br label %Block5
Block5:
	%reg_131 = phi i32 [ %reg_130, %Block4 ], [ %reg_132, %Block8 ]
	%reg_119 = phi i32 [ %reg_17, %Block4 ], [ %reg_121, %Block8 ]
	%reg_114 = phi i32 [ %reg_115, %Block4 ], [ %reg_113, %Block8 ]
	%reg_101 = add i32 1, 0
	%reg_102 = add i32 %reg_131, %reg_101
	br label %Block1
Block6:
	%reg_19 = add i32 10, 0
	%reg_20 = srem i32 %reg_130, %reg_19
	%reg_21 = add i32 1, 0
	%reg_22 = icmp eq i32 %reg_20, %reg_21
	br i1 %reg_22, label %Block7, label %Block9
Block7:
	%reg_24 = add i32 2, 0
	%reg_25 = add i32 %reg_120, %reg_24
	br label %Block8
Block8:
	%reg_132 = phi i32 [ %reg_130, %Block7 ], [ %reg_133, %Block11 ]
	%reg_121 = phi i32 [ %reg_25, %Block7 ], [ %reg_122, %Block11 ]
	%reg_113 = phi i32 [ %reg_115, %Block7 ], [ %reg_112, %Block11 ]
	br label %Block5
Block9:
	%reg_27 = add i32 10, 0
	%reg_28 = srem i32 %reg_130, %reg_27
	%reg_29 = add i32 2, 0
	%reg_30 = icmp eq i32 %reg_28, %reg_29
	br i1 %reg_30, label %Block10, label %Block12
Block10:
	%reg_32 = add i32 3, 0
	%reg_33 = add i32 %reg_120, %reg_32
	br label %Block11
Block11:
	%reg_133 = phi i32 [ %reg_130, %Block10 ], [ %reg_134, %Block14 ]
	%reg_122 = phi i32 [ %reg_33, %Block10 ], [ %reg_123, %Block14 ]
	%reg_112 = phi i32 [ %reg_115, %Block10 ], [ %reg_111, %Block14 ]
	br label %Block8
Block12:
	%reg_35 = add i32 10, 0
	%reg_36 = srem i32 %reg_130, %reg_35
	%reg_37 = add i32 3, 0
	%reg_38 = icmp eq i32 %reg_36, %reg_37
	br i1 %reg_38, label %Block13, label %Block15
Block13:
	%reg_40 = add i32 4, 0
	%reg_41 = add i32 %reg_120, %reg_40
	br label %Block14
Block14:
	%reg_134 = phi i32 [ %reg_130, %Block13 ], [ %reg_135, %Block17 ]
	%reg_123 = phi i32 [ %reg_41, %Block13 ], [ %reg_124, %Block17 ]
	%reg_111 = phi i32 [ %reg_115, %Block13 ], [ %reg_110, %Block17 ]
	br label %Block11
Block15:
	%reg_43 = add i32 10, 0
	%reg_44 = srem i32 %reg_130, %reg_43
	%reg_45 = add i32 4, 0
	%reg_46 = icmp eq i32 %reg_44, %reg_45
	br i1 %reg_46, label %Block16, label %Block18
Block16:
	%reg_48 = add i32 5, 0
	%reg_49 = add i32 %reg_120, %reg_48
	br label %Block17
Block17:
	%reg_135 = phi i32 [ %reg_130, %Block16 ], [ %reg_136, %Block20 ]
	%reg_124 = phi i32 [ %reg_49, %Block16 ], [ %reg_125, %Block20 ]
	%reg_110 = phi i32 [ %reg_115, %Block16 ], [ %reg_109, %Block20 ]
	br label %Block14
Block18:
	%reg_51 = add i32 10, 0
	%reg_52 = srem i32 %reg_130, %reg_51
	%reg_53 = add i32 5, 0
	%reg_54 = icmp eq i32 %reg_52, %reg_53
	br i1 %reg_54, label %Block19, label %Block21
Block19:
	%reg_56 = add i32 6, 0
	%reg_57 = add i32 %reg_120, %reg_56
	br label %Block20
Block20:
	%reg_136 = phi i32 [ %reg_130, %Block19 ], [ %reg_137, %Block23 ]
	%reg_125 = phi i32 [ %reg_57, %Block19 ], [ %reg_126, %Block23 ]
	%reg_109 = phi i32 [ %reg_115, %Block19 ], [ %reg_108, %Block23 ]
	br label %Block17
Block21:
	%reg_59 = add i32 10, 0
	%reg_60 = srem i32 %reg_130, %reg_59
	%reg_61 = add i32 6, 0
	%reg_62 = icmp eq i32 %reg_60, %reg_61
	br i1 %reg_62, label %Block22, label %Block24
Block22:
	%reg_64 = add i32 7, 0
	%reg_65 = add i32 %reg_120, %reg_64
	br label %Block23
Block23:
	%reg_137 = phi i32 [ %reg_130, %Block22 ], [ %reg_138, %Block26 ]
	%reg_126 = phi i32 [ %reg_65, %Block22 ], [ %reg_127, %Block26 ]
	%reg_108 = phi i32 [ %reg_66, %Block22 ], [ %reg_116, %Block26 ]
	br label %Block20
Block24:
	%reg_68 = add i32 10, 0
	%reg_69 = srem i32 %reg_130, %reg_68
	%reg_70 = add i32 7, 0
	%reg_71 = icmp eq i32 %reg_69, %reg_70
	br i1 %reg_71, label %Block25, label %Block27
Block25:
	%reg_73 = add i32 8, 0
	%reg_74 = add i32 %reg_120, %reg_73
	%reg_76 = add i32 3, 0
	%reg_77 = add i32 %reg_115, %reg_76
	br label %Block26
Block26:
	%reg_138 = phi i32 [ %reg_130, %Block25 ], [ %reg_139, %Block29 ]
	%reg_127 = phi i32 [ %reg_74, %Block25 ], [ %reg_128, %Block29 ]
	%reg_116 = phi i32 [ %reg_77, %Block25 ], [ %reg_117, %Block29 ]
	br label %Block23
Block27:
	%reg_79 = add i32 10, 0
	%reg_80 = srem i32 %reg_130, %reg_79
	%reg_81 = add i32 8, 0
	%reg_82 = icmp eq i32 %reg_80, %reg_81
	br i1 %reg_82, label %Block28, label %Block30
Block28:
	%reg_84 = add i32 9, 0
	%reg_85 = add i32 %reg_120, %reg_84
	%reg_87 = add i32 4, 0
	%reg_88 = add i32 %reg_115, %reg_87
	br label %Block29
Block29:
	%reg_139 = phi i32 [ %reg_130, %Block28 ], [ %reg_130, %Block32 ]
	%reg_128 = phi i32 [ %reg_85, %Block28 ], [ %reg_129, %Block32 ]
	%reg_117 = phi i32 [ %reg_88, %Block28 ], [ %reg_118, %Block32 ]
	br label %Block26
Block30:
	%reg_90 = add i32 10, 0
	%reg_91 = srem i32 %reg_130, %reg_90
	%reg_92 = add i32 9, 0
	%reg_93 = icmp eq i32 %reg_91, %reg_92
	br i1 %reg_93, label %Block31, label %Block32
Block31:
	%reg_95 = add i32 10, 0
	%reg_96 = add i32 %reg_120, %reg_95
	%reg_98 = add i32 11, 0
	%reg_99 = add i32 %reg_115, %reg_98
	br label %Block32
Block32:
	%reg_129 = phi i32 [ %reg_120, %Block30 ], [ %reg_96, %Block31 ]
	%reg_118 = phi i32 [ %reg_115, %Block30 ], [ %reg_99, %Block31 ]
	br label %Block29
}
