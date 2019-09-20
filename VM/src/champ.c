/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:29:19 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/20 01:34:42 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_champ(t_champ *champ)
{
	unsigned int	i;

	ft_printf("Champ[id = %d] : %s\n", champ->id, champ->h.prog_name);
	ft_printf("Comment : %s\n", champ->h.comment);
	ft_printf("Prog size : %d", champ->h.prog_size);
	ft_putstr("champ en hex : \n");
	i = -1;
	while (++i < champ->h.prog_size)
		ft_printf("%x ", champ->buff[i]);
	ft_putchar('\n');
}

t_champ		new_champ(t_arena *arena, unsigned char *buff, int ret)
{
	t_champ		champ;

	ft_bzero(&champ, sizeof(t_champ));
	ft_memcpy(&champ.h, buff, sizeof(t_header));
	champ.h.magic = chen4(champ.h.magic);
	champ.h.prog_size = chen4(champ.h.prog_size);
	if (ret - (int)sizeof(t_header) != (int)champ.h.prog_size)
		ft_error(A, "Header's prog_size doesn't correspond to champ size\n");
	if (champ.h.magic != COREWAR_EXEC_MAGIC)
		ft_error(A, "Wrong magic number !\n");
	if (champ.h.prog_size > CHAMP_MAX_SIZE)
		ft_error(A, "Champ size too big !\n");
	ft_memcpy(champ.buff, buff + sizeof(t_header), champ.h.prog_size);
	return (champ);
}

void		create_add_champ(char *filename, t_arena *arena, int id_champ)
{
	unsigned char	*buffer;
	static int		pos = 0;
	int				read_ret;

	if (!(buffer = (unsigned char*)ft_alloc_gc(CHAMP_MAX_SIZE +
					sizeof(t_header), sizeof(char), A->gc)))
		ft_error(A, "Malloc error\n");
	ft_bzero(buffer, CHAMP_MAX_SIZE + sizeof(t_header));
	read_ret = open_read(A, filename, buffer);
	A->champ[pos] = new_champ(A, buffer, read_ret);
	A->champ[pos].id = id_champ;
	pos++;
	A->nb_champ++;
}

void		sort_champ(t_arena *arena)
{
	int		i;
	int		j;
	t_champ	tmp;

	i = -1;
	while (++i < A->nb_champ - 1)
	{
		j = i;
		while (++j < A->nb_champ)
			if (A->champ[i].id < A->champ[j].id)
			{
				tmp = A->champ[i];
				A->champ[i] = A->champ[j];
				A->champ[j] = tmp;
			}
	}
}

void		load_champ(t_arena *arena)
{
	int		i;
	int		space;

	i = -1;
	space = MEM_SIZE / A->nb_champ;
	while (++i < A->nb_champ)
	{
		ft_memcpy(A->field + (i * space), A->champ[i].buff,
				A->champ[i].h.prog_size);
		fill_color_value(A->carriage + (i * space),
				A->champ[i].h.prog_size, i);
		add_process(A, A->champ[i].id, i);
		A->PRO->pc = i * space;
	}
}
