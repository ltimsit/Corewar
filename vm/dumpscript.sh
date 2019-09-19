#!/bin/sh

i=0;
while $i != 10
do	j=10*$i
	./corewar -dump $j ressources/champs/gagnant.cor > test1
	./ressources/corewar -d $j ressources/champs/gagnant.cor > test2
	diff test1 test2
	i++
done
