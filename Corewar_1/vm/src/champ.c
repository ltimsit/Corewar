/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:29:19 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/10 19:22:18 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* 
void		print_champ(t_champ *champ)
{
	unsigned int	i;

	ft_printf("Champ[id = %d] : %s\n", champ->id, champ->h.prog_name);
	ft_printf("Comment : %s\n", champ->h.comment);
	ft_printf("Prog size : %d", champ->h.prog_size);
	ft_putstr("champ en hex : \n");
	i = -1;
	while (++i < champ->h.prog_size)
	{
		btohex(champ->buff[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}
*/

t_champ		new_champ(t_arena *arena, unsigned char *buff)
{
	t_champ		champ;

	ft_bzero(&champ, sizeof(t_champ));
	ft_memcpy(&champ.h, buff, sizeof(header_t));
	champ.h.magic = change_endian(champ.h.magic);
	champ.h.prog_size = change_endian(champ.h.prog_size);
	if (champ.h.magic != COREWAR_EXEC_MAGIC)
		ft_error(arena, "WRONG MAGIC NUMBER\n");
	if (champ.h.prog_size > CHAMP_MAX_SIZE)
		ft_error(arena, "CHAMP SIZE TO BIG\n");
	ft_memcpy(champ.buff, buff + sizeof(header_t), champ.h.prog_size);
	return (champ);
}

void		create_add_champ(char *filename, t_arena *arena, int id_champ)
{
	unsigned char	*buffer;
	static int		pos = 0;

	if (!(buffer = (unsigned char*)ft_alloc_gc(CHAMP_MAX_SIZE +
					sizeof(header_t), sizeof(char), arena->gc)))
		ft_error(arena, "Malloc error\n");
	ft_bzero(buffer, CHAMP_MAX_SIZE + sizeof(header_t));
	buffer = open_read(arena, filename, buffer);
	arena->champ[pos] = new_champ(arena, buffer);
	arena->champ[pos].id = id_champ;
	pos++;
	arena->nb_champ++;
}
