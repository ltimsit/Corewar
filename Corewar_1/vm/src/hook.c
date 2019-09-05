/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:37:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/05 14:25:27 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>


int		print_nb(t_arena *arena, int nb, int x, int y)
{
	char nb_tab[10];
	int size;
	int i;

	i = 10;
	size = 0;
	while (++size && nb / i)
		i *= 10;
	nb_tab[size] = '\0';
	ft_printf("size = %d nb = %d\n", size, nb);
	while (size)
	{
		nb_tab[--size] = nb % 10 + '0';
		nb /= 10;
	}
	mlx_string_put(arena->dis->mlx, arena->dis->win, x, y, 0xFFFFFF, nb_tab);
	return (0);
}
int		key_press(int keycode, t_arena *arena)
{
	if (keycode == 53)
	{
		exit(0);
	}
	if (keycode == 49)
	{
		arena->pause = arena->pause ? 0 : 1;
	}
	if (keycode == 82 && arena->pause)
		launch_fight(arena);

	return (0);
}

int		mouse_press(int button, int x, int y, t_display *dis)
{
	(void)dis;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		loop_fight(t_arena *arena)
{
	if (!arena->pause)
	{
		launch_fight(arena);
	}
	return (0);
}
