.name "The peoples champ"
.comment "Eye of the tiger!"

l2:		ld 
		lfork 
		sti r1, %:live, %1
		lldi r1, %0, r1

live:	live %1
		zjmp %:live
