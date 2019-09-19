/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:26:32 by abinois           #+#    #+#             */
/*   Updated: 2019/09/19 18:13:24 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_reg_click(t_arena *arena, int x, int y)
{
	int			index;
	int			i;
	t_process	**p;

	p = (t_process **)&(A->dis->curr_process_dis);
	i = -1;
	index = (y - Y_OFFSET) / 20 * BYTE_PER_COL + (x - X_OFFSET) / 27;
	print_map(arena, A->curr_cycle);
	if (((A->carriage[index] >> 4) & 1) == 1)
	{
		while ((*p || (*p = A->p_head)) && ++i < A->nb_process)
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
	y = 400;
	i = -1;
	while (++i < 16)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				x - 90, y, HEX_COLOR, "reg[  ] = ");
		print_nb_dec(A, i + 1, x - 50, y);
		print_nb(A, (unsigned int)(PRO->reg[i]), x + 10, y);
		y += 20;
	}
}

int		print_nb(t_arena *arena, unsigned int nb, int x, int y)
{
	char				nb_tab[10];
	char				*base;
	int					size;
	unsigned int		nb_tmp;

	base = "0123456789abcdef";
	size = 0;
	nb_tmp = nb;
	while (++size && (nb_tmp / 16))
		nb_tmp /= 16;
	nb_tab[size] = '\0';
	while (size)
	{
		nb_tab[--size] = base[nb % 16];
		nb /= 16;
	}
	mlx_string_put(A->dis->mlx, A->dis->win, x, y, HEX_COLOR, nb_tab);
	return (0);
}

int		print_nb_dec(t_arena *arena, int nb, int x, int y)
{
	char	nb_tab[12];
	int		size;
	int		i;
	int		sign;

	i = 10;
	size = 0;
	sign = 1;
	if (nb < 0)
	{
		nb_tab[0] = '-';
		size++;
		nb *= -1;
		sign = -1;
	}
	while (++size && nb / i)
		i *= 10;
	nb_tab[size] = '\0';
	while (size--)
	{
		nb_tab[size] = (!size && sign == -1) ? '-' : (nb % 10 + '0');
		nb /= 10;
	}
	mlx_string_put(A->dis->mlx, A->dis->win, x, y, HEX_COLOR, nb_tab);
	return (0);
}

void	print_process_dis(t_arena *arena)
{
	int			nb_process;
	int			x;
	int			y;

	x = 1910;
	y = 220;
	nb_process = 0;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x - 90, y, HEX_COLOR, "process :");
	print_nb_dec(A, A->nb_process, x + 15, y);
	print_champ_live(arena);
}
