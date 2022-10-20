.name "The peoples champ"
.comment "Eye of the tiger!"

l2:		st r1, r2
		st r1, r3
		st r1, r4
		st r1, r5
		st r1, r5
		live %11
		st r1, r6
		st r1, r7
		st r1, r8
		live %11
		st r1, r9
		st r1, r10
		st r1, r11
		st r1, r12
		st r1, r13
		live %11
		fork %-4000
		st r1, r14
		st r1, r15
		st r2, 11
		st r1, -511
		live %11
		fork %13
		fork %30
		ld %0, r16
		zjmp %-80
		ld %-2, r16
		st r16, 655555
		lfork %42252
		sti r1, %:live, %1
		lldi r1, %0, r1
		sti r1, %50, %1
		ld %1, r16
		sti r1, %50, %0
		sti r2, %100, %1
		sti r1, %100, %0
		sti r3, %150, %1
		sti r1, %150, %0
		sti r4, %200, %1
		sti r1, %200, %0
		sti r5, %250, %1
		sti r1, %250, %0
		sti r6, %300, %1
		sti r1, %300, %0
		sti r7, %350, %1
		sti r1, %350, %0
		sti r8, %400, %1
		sti r1, %400, %0
		sti r9, %450, %1
		sti r1, %450, %0
		sti r10, %500, %1
		sti r11, %-500, %1
		sti r12, %-450, %1
		sti r13, %-400, %1
		sti r14, %-350, %1
		sti r15, %-300, %1
		sti r16, %-250, %1
		zjmp %-50

live:	live %1
		zjmp %:live
