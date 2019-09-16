/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:26:32 by abinois           #+#    #+#             */
/*   Updated: 2019/09/16 09:23:29 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_color_value(unsigned char *carriage, int size, int p_nb)
{
	int i;

	i = -1;
	while (++i < size)
		carriage[i] += (1 << p_nb);
}

void	clear_carriage_superpo(t_arena *arena)
{
	t_process	*tmp;
	int			i;

	tmp = A->p_head;
	i = -1;
	if (A->nb_process < 4096)
	{
		while (tmp)
		{
			if ((A->carriage[tmp->pc] >> 5) & 1)
				A->carriage[tmp->pc] ^= 1 << 5;
			tmp = tmp->next;
		}
	}
	else
		while (++i < MEM_SIZE)
			if ((A->carriage[i] >> 5) & 1)
				A->carriage[tmp->pc] ^= 1 << 5;
}

int		print_reg_click(t_arena *arena, int x, int y)
{
	int			idx;
	int			idy;
	int			index;
	t_process	**p;

	p = (t_process **)&(A->dis->curr_process_dis);
	idx = (x - X_OFFSET) / 27;
	idy = (y - Y_OFFSET) / 20;
	index = idy * BYTE_PER_COL + idx;
	print_map(arena, A->curr_cycle);
	if (((A->carriage[index] >> 4) & 1) == 1)
	{
		while (*p || (*p = A->p_head))
		{
			if ((*p)->pc == index)
			{
				print_reg_dis(arena, *p);
				*p = (*p)->next;
				return (1);
			}
			*p = (*p)->next;
		}
	}
	return (1);
}

void	print_reg_dis(t_arena *arena, t_process *process)
{
	int i;
	int x;
	int y;

	x = 1910;
	y = 200;
	i = -1;
	while (++i < 16)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				x - 90, y, HEX_COLOR, "reg[  ] = ");
		print_nb_dec(A, i + 1, x - 50, y);
		print_nb(A, process->reg[i], x + 10, y);
		y += 20;
	}
}

int		print_nb(t_arena *arena, int nb, int x, int y)
{
	char	nb_tab[10];
	char	*base;
	int		size;
	int		i;

	base = "0123456789abcdef";
	i = 16;
	size = 0;
	while (++size && nb / i)
		i *= 16;
	nb_tab[size] = '\0';
	while (size)
	{
		nb_tab[--size] = base[nb % 16];
		nb /= 16;
	}
	mlx_string_put(A->dis->mlx, A->dis->win, x, y, HEX_COLOR, nb_tab);
	return (0);
}
