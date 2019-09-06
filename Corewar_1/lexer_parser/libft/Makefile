# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 14:51:13 by abinois           #+#    #+#              #
#    Updated: 2019/07/04 12:59:27 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
CC = gcc

SRC = $(addprefix ft_, $(addsuffix .c, \
	  memset memcpy memccpy memmove memchr memcmp memalloc memdel bzero \
	  strlen strdup strcpy strncpy strcat strncat strlcat strchr strrchr \
	  strstr strnstr strcmp strncmp atoi isalpha isdigit isascii isprint \
	  isalnum putchar putstr toupper tolower putchar_fd putstr_fd putnbr \
	  putnbr_fd putendl putendl_fd strnew strdel strclr striter striteri \
	  strmap strmapi strequ strnequ strsub strjoin strtrim itoa strnrev \
	  strsplit swap lstnew lstdelone lstdel lstadd lstiter lst_size lstmap \
	  lst_rev po sqrt putstrclr get_next_line display_file putnstr fili \
	  llutoa lltoa octatoa hexatoa str_up strjoinfr str_add \
	free_stropt bitoa abs))

OBJ = $(SRC:.c=.o)

VERT = \033[32m
VIOLET = \033[35m
ROUGE = \033[31m
JAUNE = \033[33m
NOCOLOR = \033[0m
BLINK = \033[5m

all: $(NAME)
 
$(NAME): $(OBJ) Makefile libft.h
	@echo "$(VIOLET)COMPILATION . . . . . . . . . . . . . . . . .$(JAUNE)"
	(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	#ranlib $(NAME)
	@echo "$(VERT)----------------------> $(BLINK)OK !$(NOCOLOR)"

clean:
	@echo "$(VIOLET)SUPPR DES .O . . . . . . . . . . . . . . .$(ROUGE)"
	rm -f $(OBJ)
	@echo "$(VERT)----------------------> $(BLINK)OK !$(NOCOLOR)"

fclean: clean
	@echo "$(VIOLET)SUPPR DE LA LIB . . . . . . . . . . . . . .$(ROUGE)"
	rm -f $(NAME)
	@echo "$(VERT)----------------------> $(BLINK)OK !$(NOCOLOR)"

re: fclean all
	@echo "$(VIOLET)RELINK . . . . . . . . . . . . . . . . . . . ."
	@echo "$(VERT)----------------------> $(BLINK)OK !$(NOCOLOR)"

.PHONY: all clean fclean re
