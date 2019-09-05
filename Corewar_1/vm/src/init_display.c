/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:22:23 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/05 14:52:06 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_map(t_arena *arena, int c_nb)
{
	int i;

	mlx_clear_window(arena->dis->mlx, arena->dis->win);
	i = -1;
	while (++i < MEM_SIZE)
	{
		print_hexa_dis(arena, arena->dis, i);
	}
	print_nb(arena, c_nb, 1870, 0);
}

void	fill_img(char *d_img)
{
	int i;
	int *i_img;

	i_img = (int *)d_img;
	i = -1;
	while (++i < C_HGT * C_LEN)
	{
		i_img[i] = 0x770000FF;
	}
}

char	*get_data_ptr(void *img_ptr)
{
	char	*data_ptr;
	int		bit_pp;
	int		size_line;
	int		endian;

	data_ptr = mlx_get_data_addr(img_ptr, &bit_pp, &size_line, &endian);
	return (data_ptr);
}

int		print_hexa_dis(t_arena *arena, t_display *dis, int index)
{
	char *base;
	char byte;
	char nb;
	int	size;
	int line;
	int col;
//	int j;
	char	hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = arena->field[index];
	byte = arena->field[index];
	line = (index / BYTE_PER_COL) * 20;
	col = (index % BYTE_PER_COL) * 27;

	while (nb / 16)
	{
		size++;
		nb = nb / 16;
	}
	if (size == 1)
	{
		hex[0]= '0';
		size++;
	}
	hex[2] ='\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
/*
	while (++j < 4)
	{
		*/
		if (arena->carriage[index])
			mlx_put_image_to_window(dis->mlx, dis->win, dis->img, col, line);
//	}
	mlx_string_put(dis->mlx, dis->win, col, line, 0xFFFFFF, hex);
	return (1);
}


void	init_display(t_arena *arena)
{
	t_display dis;

	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, W_LEN, W_HGT, "Corewar");
	dis.img = mlx_new_image(dis.mlx, C_LEN, C_HGT);
	dis.d_img = get_data_ptr(dis.img);
	fill_img(dis.d_img);
	arena->dis = &dis;
	arena->pause = 1;
	mlx_hook(dis.win, 2, 0, key_press, arena);
	mlx_hook(dis.win, 4, 0, mouse_press, arena);
	mlx_loop_hook(dis.mlx, loop_fight, arena);
	mlx_loop(dis.mlx);
}
