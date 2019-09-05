/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:22:23 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/05 18:34:51 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_border(t_arena *arena)
{
	int x;
	int y;
	int *data;

	data = (int *)arena->dis->d_border_img;
	y = 25;
	while (++y < 64 * 21)
	{
		x = 13;
		while (++x < 64 * 28)
		{
			if ((y < 35 || y > 64 * 21 - 10) || (x < 23 || x > 64 * 28 - 10))
				data[y * W_LEN + x] = BORDER_COLOR;
			else
				data[y * W_LEN + x] = BACKGROUND_COLOR;
		}
	}
}

void	print_process_dis(t_arena *arena)
{
	t_process *tmp;
	int i;
	int x;
	int y;

	x = 1910;
	y = 40;
	tmp = arena->p_head;
	while (tmp)
	{
		i = -1;
		while (++i < 16)
		{
			mlx_string_put(arena->dis->mlx, arena->dis->win, x - 90, y, HEX_COLOR, "reg[  ] = ");
			print_nb(arena, i + 1, x - 50, y);
			print_nb(arena, tmp->reg[i], x, y);
			y += 20;
		}
		tmp = tmp->next;
	}
}

void	print_map(t_arena *arena, int c_nb)
{
	int i;

	mlx_clear_window(arena->dis->mlx, arena->dis->win);
	mlx_put_image_to_window(arena->dis->mlx, arena->dis->win, arena->dis->border_img, 0, 0);
	mlx_string_put(arena->dis->mlx, arena->dis->win, W_LEN / 2 - 30, 3, HEX_COLOR, "COREWAR");
	i = -1;
	while (++i < MEM_SIZE)
	{
		print_hexa_dis(arena, arena->dis, i);
	}
	ft_printf("nb =%d\n", c_nb);
	print_nb(arena, arena->total_cycle, 1910, 0);
	print_nb(arena, c_nb + 1, 1910, 20);
	print_process_dis(arena);
}

void	fill_img(char *d_img)
{
	int i;
	int *i_img;

	i_img = (int *)d_img;
	i = -1;
	while (++i < C_HGT * C_LEN)
	{
		i_img[i] = 0x440000FF;
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
	unsigned char byte;
	unsigned char nb;
	int	size;
	int line;
	int col;
//	int j;
	char	hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = arena->field[index];
	byte = arena->field[index];
	line = (index / BYTE_PER_COL) * 20 + Y_OFFSET;
	col = (index % BYTE_PER_COL) * 27 + X_OFFSET;

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
	if (arena->carriage[index])
		mlx_put_image_to_window(dis->mlx, dis->win, dis->img, col, line);
	mlx_string_put(dis->mlx, dis->win, col, line, HEX_COLOR, hex);
	return (1);
}


void	init_display(t_arena *arena)
{
	t_display dis;

	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, W_LEN, W_HGT, "Corewar");
	dis.img = mlx_new_image(dis.mlx, C_LEN, C_HGT);
	dis.d_img = get_data_ptr(dis.img);
	dis.border_img = mlx_new_image(dis.mlx, W_LEN, W_HGT);
	dis.d_border_img = get_data_ptr(dis.border_img);
	fill_img(dis.d_img);
	arena->dis = &dis;
	arena->pause = 1;
	fill_border(arena);
	mlx_hook(dis.win, 2, 0, key_press, arena);
	mlx_hook(dis.win, 4, 0, mouse_press, arena);
	mlx_loop_hook(dis.mlx, loop_fight, arena);
	mlx_loop(dis.mlx);
}
