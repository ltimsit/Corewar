# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 14:51:13 by abinois           #+#    #+#              #
#    Updated: 2019/09/16 11:14:49 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
CC = gcc

SRC = $(addprefix ft_, $(addsuffix .c, \
	  memset memcpy memccpy memmove memchr memcmp memalloc memdel bzero \
	  strlen strdup strcpy strncpy strcat strncat strlcat strchr strrchr \
	  strstr strnstr strcmp strncmp atoi isalpha isdigit isascii isprint \
	  isalnum putchar putstr toupper tolower putchar_fd putstr_fd putnbr abs \
	  putnbr_fd putendl putendl_fd strnew strdel strclr striter striteri \
	  strmap strmapi strequ strnequ strsub strjoin strtrim itoa strnrev \
	  strsplit swap lstnew lstdelone lstdel lstadd lstiter lst_size lstmap \
	  lst_rev po sqrt putstrclr get_next_line display_file putnstr fili sqrtup \
	  llutoa lltoa octatoa hexatoa str_up strjoinfr str_add free_stropt bitoa \
	  alloc_gc free_gc add_to_gc skip_char skip_nochar chen strnchr \
	  str_is_digit))

OBJ = $(SRC:.c=.o)

VERT = \033[32m
VIOLET = \033[35m
ROUGE = \033[31m
JAUNE = \033[33m
NOCOLOR = \033[0m
BLEU = \033[34m

NB_FILE = $(words $(SRC))
CPT = 1

all: $(NAME)
 
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n$(VIOLET)COMPILATION  $(JAUNE)LIB$(VIOLET) : $(VERT)OK !$(NOCOLOR)"
	@sleep 0.2

%.o : %.c Makefile libft.h
	@echo "\033[K$(BLEU)Compilation of file$(NOCOLOR) [$(CPT) / $(NB_FILE)] : $(VERT)$< \033[A$(NOCOLOR)"
	$(eval CPT=$(shell echo $$(($(CPT) + 1))))
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(VIOLET)SUPPR  $(JAUNE)OBJ LIB $(VIOLET):$(VERT) OK !$(NOCOLOR)"
	@echo "$(VERT)LIB CLEAN : 👌 $(NOCOLOR)"

fclean: clean
	@echo "$(VIOLET)SUPPR  $(JAUNE)LIB $(VIOLET): $(ROUGE)$(NAME)$(NOCOLOR)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
