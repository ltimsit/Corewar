/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:53:57 by abinois           #+#    #+#             */
/*   Updated: 2019/09/17 20:42:38 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	g_tab_color[5] =
{
	ORDER, ASSEMBLY, ALLIANCE, FEDERATION, WHITE
};

int		print_nb_dec(t_arena *arena, int nb, int x, int y)
{
	char	nb_tab[12];
	int		size;
	int		i;
	int		sign;

	i = 10;
	size = 0;
	sign = 1;
	if (nb < 0)
	{
		nb_tab[0] = '-';
		size++;
		nb *= -1;
		sign = -1;
	}
	while (++size && nb / i)
		i *= 10;
	nb_tab[size] = '\0';
	while (size--)
	{
		nb_tab[size] = (!size && sign == -1) ? '-' : (nb % 10 + '0');
		nb /= 10;
	}
	mlx_string_put(A->dis->mlx, A->dis->win, x, y, HEX_COLOR, nb_tab);
	return (0);
}

void	fill_border(t_arena *arena)
{
	int		x;
	int		y;
	int		*data;

	data = (int *)A->dis->d_border_img;
	y = -1;
	while (++y < BORDER_HGT)
	{
		x = -1;
		while (++x < BORDER_LEN)
		{
			if ((y < 8 || y > BORDER_HGT - 10)
					|| (x < 10 || x > BORDER_LEN - 10))
				data[y * BORDER_LEN + x] = BORDER_COLOR;
			else
				data[y * BORDER_LEN + x] = BACKGROUND_COLOR;
		}
	}
}

void	fill_img(char **d_img)
{
	int i;
	int j;
	int *i_img;
	j = -1;
	while (++j < 5)
	{
		i_img = (int *)d_img[j];
		i = -1;
		while (++i < C_HGT * C_LEN)
			i_img[i] = g_tab_color[j] + 0x74000000;
	}
}

void	print_champ_live(t_arena *arena)
{
	int i;
	int x;
	int y;

	x = 1950;
	y = 180;
	i = -1;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x, y - 20, HEX_COLOR, "live");
	while (++i < A->nb_champ)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				1820, y, g_tab_color[i], "Joueur        :");
		print_nb_dec(A, A->champ[i].id, 1885, y);
		print_nb_dec(A, A->champ[i].nb_live, 1975, y);
		y += 20;
	}
}

void	print_process_dis(t_arena *arena)
{
	int			nb_process;
	int			x;
	int			y;

	x = 1910;
	y = 120;
	nb_process = 0;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x - 90, y, HEX_COLOR, "process :");
	print_nb_dec(A, A->nb_process, x + 15, y);
	print_champ_live(arena);
}
