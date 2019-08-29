/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/28 14:18:09 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "include/vm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void	print_champ_h(t_champ *champ)
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
}

int		open_files(char *filename)
{	
	int	fd;

	fd = open(filename, O_RDONLY);	
	return (fd);
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


t_champ		create_champ(unsigned char *buff)
{	
	t_champ 		champ;

	ft_bzero(&champ,sizeof(t_champ));
	ft_memcpy(&champ.h, buff, sizeof(header_t));
	champ.h.magic = change_endian(champ.h.magic);
	champ.h.prog_size = change_endian(champ.h.prog_size);
	champ.size = champ.h.prog_size;
	if (champ.h.magic != COREWAR_EXEC_MAGIC)
		ft_error("WRONG MAGIC NUMBER\n");
	if (champ.h.prog_size > CHAMP_MAX_SIZE)
		ft_error("CHAMP SIZE TO BIG\n");

	ft_memcpy(champ.buff, buff + sizeof(header_t), champ.h.prog_size);
	return (champ);
}

int		main(int ac, char **av)
{
	int 				fd;
	t_champ 			champ;
	unsigned char 		buffer[10000];
	int 				ret;

	(void)ac;
	fd = open_files(av[1]);
	ft_bzero(buffer,9999);
	ret = read(fd, buffer, 9999);
	champ = create_champ(buffer);
//	launch_fight(&champ);
	print_champ_h(&champ);
	return (0);
}
