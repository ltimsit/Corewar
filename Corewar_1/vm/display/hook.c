/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:37:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/04 16:19:29 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include <stdlib.h>

int		display_all(t_display *dis)
{
	int i;

	i = -1;
	mlx_clear_window(dis->mlx, dis->win);
	while (++i < 120)//MEM_SIZE)
	{
		print_hexa_dis(dis->arena, dis, i);
	}
	return (0);
}

int		key_press(int keycode, t_display *dis)
{
	if (keycode == 53)
	{
		exit(0);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_display *dis)
{
	return (0);
}
