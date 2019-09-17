/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:26:45 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 19:45:29 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_color_hex(t_arena *arena, int index)
{
	int color;

	color = A->carriage[index] & 15;
	if ((A->carriage[index] >> 4) & 1)
		color = WHITE;
	else if (color == 1)
		color = ORDER;
	else if (color == 2)
		color = ASSEMBLY;
	else if (color == 4)
		color = ALLIANCE;
	else if (color == 8)
		color = FEDERATION;
	else
		color = HEX_COLOR;
	return (color);
}

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
