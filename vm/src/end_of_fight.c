/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 09:27:01 by abinois           #+#    #+#             */
/*   Updated: 2019/09/16 14:21:19 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

static char	*g_tab_color[4] =
{
	"orange", "purple", "green", "blue"
};

void	exit_fight(t_arena *arena)
{
	ft_free_gc(A->gc);
	ft_memdel((void**)A->gc, 0);
	exit(EXIT_SUCCESS);
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
	mlx_string_put(A->dis->mlx, A->dis->win, W_LEN / 2 - 80 - 250,
			W_HGT / 2 - 35, 0xFFFFFF, "Joueur gagnant :");
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

void	print_winner(t_arena *arena)
{
	int i;

	A->finish = 1;
	if ((i = check_valid_champ(A->last_living_champ, A)) == -1)
	{
		ft_printf("☠️  Personne n'est en vie ! ☠️ \n");
		ft_free_gc(A->gc);
		ft_memdel((void**)&(A->gc), 0);
		exit(1);
	}
	else
	{
		if (A->dis)
			print_winner_dis(A, i);
		else
		{
			ft_printf("😎  Le joueur {%s}%s{reset} a gagné ! 😎 \n",
					g_tab_color[i], A->champ[i].h.prog_name);
			ft_free_gc(A->gc);
			ft_memdel((void**)&(A->gc), 0);
			exit(1);
		}
	}
}
