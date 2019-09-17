# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 09:35:38 by abinois           #+#    #+#              #
#    Updated: 2019/09/17 10:21:56 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRCS = $(addprefix $(SRCDIR)/, $(addsuffix .c, \
	   arena main operation process tools tools2 fill_tab champ \
	   addsub orxor st ld ldi and_zjump fork live_aff end_of_fight\
	   init_display hook display_tools display_tools2))

OBJ = $(SRCS:.c=.o)
DEP = $(SRCS:.c=.d)

SRCDIR = src
LIBFT = ../libft/libft.a
LIBNCURSES = -lncurses
LIBFTPRINTF = ../libftprintf.a
LIBMLX = ../libmlx.a
FRAMEWORK = -framework OpenGL -framework AppKit
INC = -I include -I ../libft

FLAGS = -Wall -Wextra -Werror
CC = gcc $(INC) $(FLAGS)

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
UNDER = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
NOCOLOR = \033[0m

NB_FILE = $(words $(SRCS))
CPT = 1

all : $(NAME)


$(NAME) : $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBFTPRINTF) $(LIBNCURSES) $(LIBMLX) $(FRAMEWORK)
	@echo "\n                               $(BLINK)👌  $(NOCOLOR)$(GREEN)A L L   G O O D $(NOCOLOR)$(BLINK)👌 $(NOCOLOR)"

-include $(DEP)

$(SRCDIR)/%.o : $(SRCDIR)/%.c makefile
	@echo "\033[K$(BLUE)Compilation of file$(NOCOLOR) [$(CPT) / $(NB_FILE)] : $(GREEN)$<\033[A$(NOCOLOR)"
	$(eval CPT=$(shell echo $$(($(CPT) + 1))))
	@gcc $(FLAGS) $(INC) -MMD -MP -c $< -o $@ 

$(LIBFT) : force
	@make -C ../libft

force :

clean :
	@make clean -C ../libft
	@rm -f $(OBJ)
	@echo "$(MAGENTA)SUPPR  $(YELLOW)OBJ $(MAGENTA): $(GREEN) OK !$(NOCOLOR)"
	@rm -f $(DEP)
	@echo "$(MAGENTA)SUPPR  $(YELLOW)DEP $(MAGENTA): $(GREEN) OK !$(NOCOLOR)"

fclean : clean
	@make fclean -C ../libft
	@echo "$(MAGENTA)SUPPR  $(YELLOW)EXE$(MAGENTA): $(RED)$(NAME)$(NOCOLOR)"
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all force
