.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		add r1, r1, r1

live:	live %1
		zjmp %:live
