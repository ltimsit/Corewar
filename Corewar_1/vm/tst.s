.name "zork"
.comment "just a basic living prog"
l2:	sti r1, %:bb, %1 
bb:	sti r1, %:and, %1 
and:	and r1, %0, r1
live: 	live %1
		zjmp %:live	
