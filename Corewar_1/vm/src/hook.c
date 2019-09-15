/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:37:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/15 17:42:20 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

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

int		print_nb_dec(t_arena *arena, int nb, int x, int y)
{
	char	nb_tab[10];
	int		size;
	int		i;

	i = 10;
	size = 0;
	while (++size && nb / i)
		i *= 10;
	nb_tab[size] = '\0';
	while (size)
	{
		nb_tab[--size] = nb % 10 + '0';
		nb /= 10;
	}
	mlx_string_put(A->dis->mlx, A->dis->win, x, y, HEX_COLOR, nb_tab);
	return (0);
}

int		key_press(int keycode, t_arena *arena)
{
	int		i;

	i = -1;
	if (keycode == 53)
		exit(0);
	if (keycode == 49)
	{
		A->pause = A->pause ? 0 : 1;
		if (A->pause == 1)
			A->dis->curr_process_dis = A->p_head;
	}
	if (keycode == 82 && A->pause)
	{
		while (A->dis->cpt_to_speed < A->dis->speed)
			launch_fight(A);
		A->dis->cpt_to_speed = 0;
		A->dis->curr_process_dis = A->p_head;
	}
	if (keycode == 126)
	{
		A->dis->speed++;
		A->dis->cpt_to_speed = 0;
		if (A->pause)
			print_map(arena, A->curr_cycle);
	}
	if (keycode == 125 && A->dis->speed > 1)
	{
		A->dis->speed--;
		A->dis->cpt_to_speed = 0;
		if (A->pause)
			print_map(arena, A->curr_cycle);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_arena *arena)
{
	if (button == 1 && A->pause)
		print_reg_click(arena, x, y);
	return (0);
}

int		loop_fight(t_arena *arena)
{
	if (!A->pause && !A->finish)
		launch_fight(A);
	if (A->dis->cpt_to_speed == A->dis->speed)
		A->dis->cpt_to_speed = 0;
	return (0);
}
