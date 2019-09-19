.name "Pas de stress y'a .s"
.comment "Pas de remords y'a .cor"

sti r1, %:live0, %1
sti r1, %:live1, %1
sti r1, %:live2, %1
sti r1, %:live3, %1
sti r1, %:live4, %1
live0: live %42
and r2, r2, r2
fork %16
and r2, r2, r2
fork %8
and r2, r2, r2
live1: live %42
live2: live %42
live3: live %42
live4: live %42
zjmp %:live1
