/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:22:23 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/04 16:16:33 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int		print_hexa_dis(t_arena *arena, t_display *dis, int index)
{
	char *base;
	char byte;
	char nb;
	int	size;
	int line;
	int col;
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
	mlx_string_put(dis->mlx, dis->win, col, line, 0xFFFFFF, hex);
	return (1);
}


void	init_display(t_arena *arena)
{
	t_display dis;

	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, W_LEN, W_HGT, "Corewar");
	dis.img = mlx_new_image(dis.mlx, W_LEN, W_HGT);
	dis.arena = arena;

	mlx_hook(dis.win, 2, 0, key_press, &dis);
	mlx_hook(dis.win, 4, 0, mouse_press, &dis);
	mlx_loop_hook(dis.mlx, display_all, &dis);
	mlx_loop(dis.mlx);
}

int main()
{
	t_arena arena;
	int i;
	
	i = -1;
	while (++i < 120)
	{
		arena.field[i] = i;
	}
	init_display(&arena);
}
