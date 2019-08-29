/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/29 19:10:05 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "include/vm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void	print_champ(t_champ *champ)
{
	unsigned int i;

	ft_putstr("Name : ");
	ft_putstr(champ->h.prog_name);
	ft_putchar('\n');
	ft_putstr("Comment : ");
	ft_putstr(champ->h.comment);
	ft_putchar('\n');
	ft_putstr("Prog size : ");
	ft_putnbr(champ->h.prog_size);
	ft_putchar('\n');
	ft_putstr("champ en hex : \n");
	i = -1;
	while (++i < champ->h.prog_size)
	{
		btohex(champ->buff[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

unsigned char		*open_read(char *filename, unsigned char *buffer)
{	
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);	
	if (fd == -1)
		ft_error("Open failed\n");
	ret = read(fd, buffer, 10000);
	return (buffer);
}

unsigned int change_endian(unsigned int little)
{
	unsigned char 	t_little[4];
	unsigned char 	t_big[4];
	unsigned int 	big;
	int				i;

	i = -1;
	ft_memcpy(t_little, &little, sizeof(unsigned int));
	while (++i < 4)
		t_big[i]= t_little[3 -i];
	ft_memcpy(&big, t_big, sizeof(unsigned int));
	return (big);
}

t_champ		new_champ(unsigned char *buff)
{	
	t_champ 		champ;

	ft_bzero(&champ,sizeof(t_champ));
	ft_memcpy(&champ.h, buff, sizeof(header_t));
	champ.h.magic = change_endian(champ.h.magic);
	champ.h.prog_size = change_endian(champ.h.prog_size);
	if (champ.h.magic != COREWAR_EXEC_MAGIC)
		ft_error("WRONG MAGIC NUMBER\n");
	if (champ.h.prog_size > CHAMP_MAX_SIZE)
		ft_error("CHAMP SIZE TO BIG\n");
	ft_memcpy(champ.buff, buff + sizeof(header_t), champ.h.prog_size);
	return (champ);
}

void	create_add_champ(char *filename, t_arena *arena)
{
	unsigned char	*buffer;
	static int  	id_champ = 0;
	
	if (!(buffer = (unsigned char*)malloc(sizeof(char) * 10000)))
		ft_error("Malloc error\n");
	ft_bzero(buffer, 10000);
	buffer = open_read(filename, buffer);
	arena->champ[id_champ] = new_champ(buffer);
	id_champ++;
}

int		main(int ac, char **av)
{
	int 	i;
	t_arena arena;
	
	i = 0;
	ft_bzero(&arena,sizeof(arena));
	while (i + 1 < ac)
	{
		create_add_champ(av[i + 1], &arena);
		print_champ(&arena.champ[i]);
		i++;
	}
	launch_fight(&arena);
	return (0);
}
