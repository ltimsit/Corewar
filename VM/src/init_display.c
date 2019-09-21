/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:22:23 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/21 14:56:21 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_map(t_arena *arena, int c_nb)
{
	int i;

	mlx_clear_window(A->dis->mlx, A->dis->win);
	mlx_put_image_to_window(A->dis->mlx, A->dis->win,
			A->dis->border_img, 13, 20);
	mlx_put_image_to_window(A->dis->mlx, A->dis->win,
			A->dis->panel_img, 1790, 20);
	i = -1;
	while (++i < MEM_SIZE)
		print_hexa_dis(A, A->dis, i);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 160, HEX_COLOR, "total   :");
	print_nb_dec(A, A->total_cycle, 1925, 160);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 180, HEX_COLOR, "cycle   :");
	print_nb_dec(A, c_nb, 1925, 180);
	mlx_string_put(A->dis->mlx, A->dis->win, 2000, 180, HEX_COLOR, "/");
	print_nb_dec(A, A->cycle_to_die, 2010, 180);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 200, HEX_COLOR, "speed   :");
	print_nb_dec(A, A->dis->speed, 1925, 200);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 240, HEX_COLOR, "check   :");
	print_nb_dec(A, A->nb_check, 1925, 240);
	mlx_string_put(A->dis->mlx, A->dis->win, 2000, 240, HEX_COLOR, "/");
	print_nb_dec(A, MAX_CHECKS, 2010, 240);
	put_image(A);
	print_aff(A);
	print_process_dis(A);
}

int		print_hexa_dis(t_arena *arena, t_display *dis, int index)
{
	char			*base;
	unsigned char	byte;
	int				size;
	int				cl[2];
	char			hex[3];

	base = "0123456789abcdef";
	size = 2;
	byte = A->field[index];
	cl[1] = (index / BYTE_PER_COL) * 20 + Y_OFFSET;
	cl[0] = (index % BYTE_PER_COL) * 27 + X_OFFSET;
	hex[2] = '\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
	put_carriage(A, cl[0], cl[1], index);
	mlx_string_put(dis->mlx, dis->win, cl[0], cl[1],
			get_color_hex(A, index), hex);
	return (1);
}

int		get_image_data(t_arena *arena, t_display *dis)
{
	int i;

	i = -1;
	while (++i < 5)
		if (!(dis->img[i] = mlx_new_image(dis->mlx, C_LEN, C_HGT))
				|| !ft_add_to_gc(dis->img[i], A->gc))
			return (0);
	i = -1;
	while (++i < 5)
		dis->d_img[i] = get_data_ptr(dis->img[i]);
	if (!(dis->border_img = mlx_new_image(dis->mlx, BORDER_LEN, BORDER_HGT))
			|| !ft_add_to_gc(dis->border_img, A->gc)
			|| !(dis->panel_img = mlx_new_image(dis->mlx, P_LEN, P_HGT))
			|| !ft_add_to_gc(dis->panel_img, A->gc)
			|| !init_xpm(A))
		return (0);
	dis->d_border_img = get_data_ptr(dis->border_img);
	dis->d_panel_img = get_data_ptr(dis->panel_img);
	fill_img(dis->d_img);
	return (1);
}

void	init_display(t_arena *arena)
{
	t_display	dis;

	ft_bzero(&dis, sizeof(dis));
	if (!(dis.mlx = mlx_init()) || !ft_add_to_gc(dis.mlx, A->gc))
		exit_dis(A);
	dis.win = mlx_new_window(dis.mlx, W_LEN, W_HGT, "Corewar");
	A->dis = &dis;
	if (!(get_image_data(A, &dis)))
		exit_dis(A);
	dis.speed = 1;
	dis.curr_process_dis = A->p_head;
	A->pause = 1;
	fill_border(A);
	fill_panel(A);
	print_map(A, A->curr_cycle);
	mlx_hook(dis.win, 17, 0, exit_dis, A);
	mlx_hook(dis.win, 2, 0, key_press, A);
	mlx_hook(dis.win, 4, 0, mouse_press, A);
	mlx_loop_hook(dis.mlx, loop_fight, A);
	mlx_loop(dis.mlx);
}
