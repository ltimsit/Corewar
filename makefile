# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 19:30:08 by abinois           #+#    #+#              #
#    Updated: 2019/09/19 19:56:10 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = corewar

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
MAGENTA = \033[35m
NC = \033[0m

all: $(ASM) $(COREWAR)

$(ASM):
	@make -sC assembleur

$(COREWAR):
	@make -sC vm

clean:
	@make clean -sC assembleur && make clean -sC vm

fclean:
	@make fclean -sC assembleur && make fclean -sC vm

re: fclean all

.PHONY : clean fclean re all force asm corewar
