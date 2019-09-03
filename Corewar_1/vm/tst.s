.name "zork"
.comment "just a basic living prog"

l2:	sti r1, %:live, %1 
and:	and r1, %0, r1
		or r1, %15, r2
		xor r2, %1, r3
		sub r2, r3, r4
live: 	live %1
		zjmp %:and
