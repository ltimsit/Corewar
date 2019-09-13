/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:37:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/13 09:04:24 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

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
		A->pause = A->pause ? 0 : 1;
	if (keycode == 82 && A->pause)
	{
		while (A->dis->cpt_to_speed < A->dis->speed)
			launch_fight(A);
		A->dis->cpt_to_speed = 0;
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
	if (!A->pause)
		launch_fight(A);
	if (A->dis->cpt_to_speed == A->dis->speed)
		A->dis->cpt_to_speed = 0;
	return (0);
}
