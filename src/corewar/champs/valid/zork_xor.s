.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		xor r1, %252, r1

live:	live %1
		zjmp %:live
