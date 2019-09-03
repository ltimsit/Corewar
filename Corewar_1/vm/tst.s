.name "zork"
.comment "just a basic living prog"

and:	xor r1, %1, r1
		st r1, 0
		st r1, r2
		ld 0, r2
		add r1, r1, r1
		or r1, %15, r2
		sub r1, r1, r1
		and r1, %0, r1
		xor r2, %1, r3
		sub r2, r3, r4
		and r1, %0, r1
live: 	live %1
		zjmp %:and
