/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:53:57 by abinois           #+#    #+#             */
/*   Updated: 2019/09/19 18:04:02 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	g_tab_color[5] =
{
	ORDER, ASSEMBLY, ALLIANCE, FEDERATION, WHITE
};

void	fill_color_value(unsigned char *carriage, int size, int p_nb)
{
	int i;

	i = -1;
	while (++i < size)
		carriage[i] += (1 << p_nb);
}


void	print_aff(t_arena *arena)
{
	int i;
	int x;

	if ((A->dis->aff)[0])
	{
		i = ft_strlen(A->dis->aff);
		x = 1990 - 5 * i;
		mlx_put_image_to_window(A->dis->mlx, A->dis->win,
				A->dis->bulle_xpm_img, 1830, 830);
		mlx_string_put(A->dis->mlx, A->dis->win, x, 920,
				g_tab_color[A->dis->aff_color], A->dis->aff);
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
	y = 290;
	i = -1;
	mlx_string_put(A->dis->mlx, A->dis->win,
			x, y - 20, HEX_COLOR, "live");
	ft_printf("%d\n", A->champ[0].nb_live);
	while (++i < A->nb_champ)
	{
		mlx_string_put(A->dis->mlx, A->dis->win,
				1820, y, g_tab_color[i], "Joueur        :");
		print_nb_dec(A, A->champ[i].id, 1885, y);
		print_nb_dec(A, A->champ[i].nb_live, 1975, y);
		y += 20;
	}
}

int		get_color_hex(t_arena *arena, int index)
{
	int color;

	color = A->carriage[index] & 15;
	if ((A->carriage[index] >> 4) & 1)
		color = WHITE;
	else if (color == 1)
		color = ORDER;
	else if (color == 2)
		color = ASSEMBLY;
	else if (color == 4)
		color = ALLIANCE;
	else if (color == 8)
		color = FEDERATION;
	else
		color = HEX_COLOR;
	return (color);
}
