---------------------------------------------------------------------
       ______.                                        
      / ____/  ____     _____.  ___   ._.     __   ____ _   _____.
     / /      / __ \   / ___/  / _ \  | | /| / /  / __ `/  / ___/
    / /___.  / /_/ /  / /     /  __/  | |/ |/ /  / /_/ /  / /    
    \____/   \____/  /_/      \___/   |__/|__/   \__,_/  /_/     

--------------------------------------------------------------------

This project is splitted in three parts : 
  - The champion : a .s file (written in pseudo assemlby).
  - The assembler : an executable ./asm that compiles champion files
    into .cor files (written in bytecode, in big endian).
  - The VM : an executable ./corewar that takes .cor files in arguments
    and make them fight against eachothers in a virutal memory arena (circular buffer).

If we take a basic champion like ZORK :

       .name "zork"
       .comment "I'M ALIIIIVE"

       l2:		sti r1, %:live, %1
		        and r1, %0, r1
				
       live:	live %1
				zjmp %:live

The command .name sets the champion's name.
The command .comment sets the champion's comment.
It has 2 labels : "l2" and "live" and 4 instructions : sti, and, live, zjmp.
Each instruction has its parameters that can be of 3 different types : 
  Register (from 1 to 16), Direct (a number on 4 or 2 octects)
  and Index (memory address on two octets)

We are allowed to use a set of 16 instructions two write our champion:
	- live (tells that a champion is "alive")
	- ld (loads data into a register)
	- st (store the content of a register somewhere in memory)
	- add (adds 2 contents and loads the result into a register)
	- sub (same as add but with substraction)
	- and (make a binary & between 2 contents and loads the result into a register)
	- or (same with binary | )
	- xor (same with ^ )
	- zjmp (jump to a memory address)
	- ldi (make the sum of 2 parameters and use the result as an address where to load)
	- sti (make the sum of 2 parameters and use the result as an address where to store)
	- fork (forks a process to create 2 out of 1)
	- lld (same as ld but without restricted addresses)
	- lldi (same as ldi but without restricted addresses)
	- lfork (same as fork but without restricted addresses)
	- aff (display the content of a register % 256)

For each instruction is an opcode from 01 to 16,
followed in memory by an OCP : Octet Coding Parameters
wich gives the number and the type of parameters.

After compilation, our ZORK champion looks like that (in hexadecimal):

   0b 68 01 00 0f 00 01 06 64 01 00 00 00 00 01 01 00 00 00 01 09 ff fb

The VM creates a process by champion that reads the instructions and executes them.
The last champion who was reported "alive" wins.
Each instruction takes a different number of cycles to be executed
(from aff that takes only 2 cycles, to lfork that takes 1000). Choose your strat!
Each process has 16 registers (4 octets) at disposition to stock data.
Each CYCLE_TO_DIE cycle, the VM checks the number of "live" executed by processes
and kill thoses who haven't done at least one.
CYCLE_TO_DIE is then reduced by CYCLE_DELTA and the current cycle is reset to 0.

If you understood something, congratulation ! 🤝
You can check the school Subject.pdf fore more infos.

This project was done by abinois, avanhers and ltimsit.
👌 enjoy:)

Corewar demo with our displayer:
The displayer use the Minilibx witch is a light graphical library using openGL
![alt text](https://github.com/ltimsit/Corewar/blob/master/images/Screen%20Recording%202019-12-12%20at%202.23.00%20PM.gif "Corewar demo")
