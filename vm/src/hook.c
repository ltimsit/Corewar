/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:37:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 20:42:39 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

char	*get_data_ptr(void *img_ptr)
{
	char	*data_ptr;
	int		bit_pp;
	int		size_line;
	int		endian;

	data_ptr = mlx_get_data_addr(img_ptr, &bit_pp, &size_line, &endian);
	return (data_ptr);
}

void	speed_tool(t_arena *arena, char option)
{
	if (option == '-')
		A->dis->speed--;
	else if (option == '+')
		A->dis->speed++;
	A->dis->cpt_to_speed = 0;
	if (A->pause)
		print_map(A, A->curr_cycle);
}

int		key_press(int keycode, t_arena *arena)
{
	if (keycode == 53)
		exit_dis(A);
	if (keycode == 49)
	{
		A->pause = A->pause ? 0 : 1;
		if (A->pause == 1)
			A->dis->curr_process_dis = A->p_head;
	}
	if (keycode == 82 && A->pause)
	{
		while (A->dis->cpt_to_speed < A->dis->speed && !A->finish)
			launch_fight(A);
		A->dis->cpt_to_speed = 0;
		A->dis->curr_process_dis = A->p_head;
	}
	if (keycode == 126 && A->dis->speed < 100)
		speed_tool(A, '+');
	if (keycode == 125 && A->dis->speed > 1)
		speed_tool(A, '-');
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

int		mouse_press(int button, int x, int y, t_arena *arena)
{
	if (button == 1 && A->pause)
		print_reg_click(arena, x, y);
	return (0);
}
