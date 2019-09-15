/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:22:23 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/15 18:49:44 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_border(t_arena *arena)
{
	int		x;
	int		y;
	int		*data;

	data = (int *)A->dis->d_border_img;
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

void	print_reg_dis(t_arena *arena, t_process *process)
{
	int i;
	int x;
	int y;

	x = 1910;
	y = 200;
	i = -1;
	while (++i < 16)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				x - 90, y, HEX_COLOR, "reg[  ] = ");
		print_nb_dec(A, i + 1, x - 50, y);
		print_nb(A, process->reg[i], x + 10, y);
		y += 20;
	}
}

void	print_champ_live(t_arena *arena)
{
	int i;
	int x;
	int y;

	x = 1910;
	y = 120;
	i = -1;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x, y - 20, HEX_COLOR, "live");
	while (++i < A->nb_champ)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				x - 65, y, HEX_COLOR, "Joueur    =");
		print_nb_dec(A, A->champ[i].id, x, y);
		print_nb_dec(A, A->champ[i].nb_live, x + 60, y);
		y += 20;
	}
}

void	print_process_dis(t_arena *arena)
{
	int			nb_process;
	int			x;
	int			y;

	x = 1910;
	y = 60;
	nb_process = 0;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x - 90, y, HEX_COLOR, "process :");
	print_nb_dec(A, A->nb_process, x + 60, y);
	print_champ_live(arena);
}

void	print_map(t_arena *arena, int c_nb)
{
	int i;

	mlx_clear_window(A->dis->mlx, A->dis->win);
	mlx_put_image_to_window(A->dis->mlx, A->dis->win,
			A->dis->border_img, 0, 0);
	mlx_string_put(A->dis->mlx, A->dis->win,
			W_LEN / 2 - 30, 3, HEX_COLOR, "COREWAR");
	i = -1;
	while (++i < MEM_SIZE)
	{
		print_hexa_dis(A, A->dis, i);
	}
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 0, HEX_COLOR, "total :");
	print_nb_dec(A, A->total_cycle, 1910, 0);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 20, HEX_COLOR, "cycle :");
	print_nb_dec(A, c_nb + 1, 1910, 20);
	mlx_string_put(A->dis->mlx, A->dis->win, 1820, 40, HEX_COLOR, "speed :");
	print_nb_dec(A, A->dis->speed, 1910, 40);
	print_process_dis(A);
}

void	fill_img(char **d_img)
{
	int i;
	int j;
	int *i_img;
	int	color_tab[5];

	color_tab[0] = 0x74fe704c;
	color_tab[1] = 0x749159ad;
	color_tab[2] = 0x7434c57f;
	color_tab[3] = 0x74488ed4;
	color_tab[4] = 0x74FFFFFF;
	j = -1;
	while (++j < 5)
	{
		i_img = (int *)d_img[j];
		i = -1;
		while (++i < C_HGT * C_LEN)
			i_img[i] = color_tab[j];
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

void	aff_winner(t_arena *arena, int color, char *name)
{
	int i;
	int j;
	int x_name;

	j = (W_HGT / 2) - 31;
	while (++j < (W_HGT / 2) + 70)
	{
		i = (W_LEN / 2) - 431;
		while (++i < (W_LEN / 2) - 30)
			mlx_pixel_put(A->dis->mlx, A->dis->win, i, j, 0x77000000);
	}
	j = (W_HGT / 2) - 51;
	while (++j < (W_HGT / 2) + 50)
	{
		i = (W_LEN / 2) - 451;
		while (++i < (W_LEN / 2) - 50)
			mlx_pixel_put(A->dis->mlx, A->dis->win, i, j, color);
	}
	x_name = ft_strlen(name);
	x_name = W_LEN / 2 - (x_name * 5);
	mlx_string_put(A->dis->mlx, A->dis->win, W_LEN / 2 - 80 - 250, W_HGT / 2 - 35,
			0xFFFFFF, "Joueur gagnant :");
	mlx_string_put(A->dis->mlx, A->dis->win, x_name - 250, W_HGT / 2 + 5,
			0xFFFFFF, name);
}

void	print_winner_dis(t_arena *arena, int i)
{
	char *name;

	A->finish = 1;
	name = A->champ[i].h.prog_name;
	if (i == 0)
		i = 0xff704c;
	else if (i == 1)
		i = 0x9159af;
	else if (i == 2)
		i = 0x34cf7f;
	else if (i == 3)
		i = 0x488edf;
	else
		i = HEX_COLOR;
	aff_winner(A, i, name);
}

int		print_hexa_dis(t_arena *arena, t_display *dis, int index)
{
	int				color;
	int				k;
	char			*base;
	unsigned char	byte;
	unsigned char	nb;
	int				size;
	int				line;
	int				col;
	char			hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = A->field[index];
	byte = A->field[index];
	line = (index / BYTE_PER_COL) * 20 + Y_OFFSET;
	col = (index % BYTE_PER_COL) * 27 + X_OFFSET;
	color = A->carriage[index] & 15;
	if ((A->carriage[index] >> 4) & 1)
		color = 0xffffff;
	else if (color == 1)
		color = 0xff704c;
	else if (color == 2)
		color = 0x9159af;
	else if (color == 4)
		color = 0x34cf7f;
	else if (color == 8)
		color = 0x488edf;
	else
		color = HEX_COLOR;
	if (A->carriage[index] & 32)
		color += 77;
	while (nb / 16)
	{
		size++;
		nb = nb / 16;
	}
	if (size == 1)
	{
		hex[0] = '0';
		size++;
	}
	hex[2] = '\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
	if ((A->carriage[index] >> 4) & 1)
	{
		k = -1;
		while (++k < 3)
			if ((A->carriage[index] >> k) & 1)
			{
				mlx_put_image_to_window(dis->mlx, dis->win, dis->img[k], col, line);
				break ;
			}
		mlx_put_image_to_window(dis->mlx, dis->win, dis->img[k], col, line);
	}
	mlx_string_put(dis->mlx, dis->win, col, line, color, hex);
	return (1);
}

void	init_display(t_arena *arena)
{
	t_display	dis;
	int			i;

	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, W_LEN, W_HGT, "Corewar");
	i = -1;
	while (++i < 5)
		dis.img[i] = mlx_new_image(dis.mlx, C_LEN, C_HGT);
	i = -1;
	while (++i < 5)
		dis.d_img[i] = get_data_ptr(dis.img[i]);
	dis.border_img = mlx_new_image(dis.mlx, W_LEN, W_HGT);
	dis.d_border_img = get_data_ptr(dis.border_img);
	fill_img(dis.d_img);
	dis.speed = 1;
	dis.curr_process_dis = A->p_head;
	A->dis = &dis;
	A->pause = 1;
	fill_border(A);
	print_map(A, A->curr_cycle);
	mlx_hook(dis.win, 2, 0, key_press, A);
	mlx_hook(dis.win, 4, 0, mouse_press, A);
	mlx_loop_hook(dis.mlx, loop_fight, A);
	mlx_loop(dis.mlx);
}
