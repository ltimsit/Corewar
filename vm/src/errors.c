/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:52:43 by abinois           #+#    #+#             */
/*   Updated: 2019/09/19 14:12:56 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

int		check_reg_num(t_param *param, int i)
{
	int		tmp;

	tmp = chen4(param->value[i]);
	if (tmp < 1 || tmp > 16)
	{
		param->error = 1;
		return (0);
	}
	return (1);
}

void	exit_dump(t_arena *arena)
{
	print_arena(A);
	ft_free_gc(A->gc);
	ft_memdel((void**)&(A->gc), 0);
	exit(EXIT_FAILURE);
}

void	ft_error(t_arena *arena, char *message)
{
	ft_free_gc(A->gc);
	ft_memdel((void**)&(A->gc), 0);
	ft_printf("{red}%s{reset}", message);
	exit(EXIT_FAILURE);
}

int		check_id(t_arena *arena, char *str)
{
	int i;
	int nb;

	i = -1;
	if (ft_str_is_digit(str) && is_integer(str))
	{
		nb = ft_atoi(str);
		if (nb > 1000 || nb < -1000)
			return (0);
		else
		{
			while (++i < A->nb_champ)
				if (A->champ[i].id == nb)
				{
					ft_error(A, "2 champs with same id");
					return (0);
				}
		}
		return (1);
	}
	return (0);
}

void	print_usage(t_arena *arena)
{
	ft_printf("{orange}{rev}");
	ft_printf("Usage:{%s}{%s} ./corewar [-n N <champ1.cor>] [-dis N -dump N]\n",
		"reset", "orange");
	ft_printf("{blue}\t-dis N\t\t\t: Mlx output mode start at cycle N.\n");
	ft_printf("\t-dump N\t\t\t: Dumps memory after N cycles then exits.\n");
	ft_printf("\t-n N <champ.cor>\t: Sets champion id to N [-1K < N > 1K].\n");
	ft_printf("{reset}");
	ft_free_gc(A->gc);
	ft_memdel((void**)&(A->gc), 0);
	exit(EXIT_FAILURE);
}
