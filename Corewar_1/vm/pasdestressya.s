.name "Pas de stress y'a .s"
.comment "pas de remords y'a .cor"

sti r1, %:live, %1
live %42
ld :stlabel, r2
ld :jump, r3
fork %25
stlabel: st r2, %512
jump: zjump %512


