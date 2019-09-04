/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:29:19 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/04 15:24:27 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	ft_putchar('\n');
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

void    create_add_champ(char *filename, t_arena *arena)
{
    unsigned char    *buffer;
    static int      id_champ = 12;
    static int         pos = 0;;
    if (!(buffer = (unsigned char*)ft_alloc_gc(CHAMP_MAX_SIZE +
                    sizeof(header_t), sizeof(char), arena->gc)))
        ft_error("Malloc error\n");
    ft_bzero(buffer, CHAMP_MAX_SIZE + sizeof(header_t));
    buffer = open_read(filename, buffer);
    arena->champ[pos] = new_champ(buffer);
    arena->champ[pos].id = id_champ;
    id_champ++;
    pos++;
    arena->nb_champ++;
}
