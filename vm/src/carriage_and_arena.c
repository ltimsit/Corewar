/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_and_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:26:45 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/18 09:22:19 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_carriage(t_arena *arena, int col, int line, int index)
{
	int k;

	if ((A->carriage[index] >> 4) & 1)
	{
		k = -1;
		while (++k < 3)
			if ((A->carriage[index] >> k) & 1)
			{
				mlx_put_image_to_window(A->dis->mlx, A->dis->win,
						A->dis->img[k], col, line);
				break ;
			}
		mlx_put_image_to_window(A->dis->mlx, A->dis->win,
				A->dis->img[k], col, line);
	}
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

void	fill_panel(t_arena *arena)
{
	int		x;
	int		y;
	int		*data;

	data = (int *)A->dis->d_panel_img;
	y = -1;
	while (++y < P_HGT)
	{
		x = -1;
		while (++x < P_LEN)
		{
			if ((y < 10 || y > P_HGT - 10)
					|| (x < 10 || x > P_LEN - 10))
				data[y * P_LEN + x] = P_BORDER_COLOR;
			else
				data[y * P_LEN + x] = P_BACKGROUND_COLOR;
		}
	}
}

void	fill_border(t_arena *arena)
{
	int		x;
	int		y;
	int		*data;

	data = (int *)A->dis->d_border_img;
	y = -1;
	while (++y < BORDER_HGT)
	{
		x = -1;
		while (++x < BORDER_LEN)
		{
			if ((y < 8 || y > BORDER_HGT - 10)
					|| (x < 10 || x > BORDER_LEN - 10))
				data[y * BORDER_LEN + x] = BORDER_COLOR;
			else
				data[y * BORDER_LEN + x] = BACKGROUND_COLOR;
		}
	}
}
