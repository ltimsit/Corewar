# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 19:30:08 by abinois           #+#    #+#              #
#    Updated: 2019/09/19 23:37:51 by abinois          ###   ########.fr        #
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
	@make -sC ASM

$(COREWAR):
	@make -sC VM

clean:
	@make clean -sC ASM && make clean -sC VM

fclean:
	@make fclean -sC ASM && make fclean -sC VM

re: fclean all

.PHONY : clean fclean re all force asm corewar
