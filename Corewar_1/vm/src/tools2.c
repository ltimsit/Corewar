/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:52:43 by abinois           #+#    #+#             */
/*   Updated: 2019/09/12 10:32:53 by abinois          ###   ########.fr       */
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
	free(A->gc);
	exit(1);
}

void	ft_error(t_arena *arena, char *message)
{
	ft_free_gc(A->gc);
	free(A->gc);
	ft_printf("{red}%s{reset}\n", message);
	exit(EXIT_FAILURE);
}

int		update_pc(int old_pc, int i)
{
	return ((old_pc + i) % MEM_SIZE);
}

void	print_usage(t_arena *arena)
{
	ft_printf("Usage: ./corewar [-n N <champion1.cor>] [-dis -dump N]\n");
	ft_printf("\t-dis\t\t\t: Mlx output mode\n");
	ft_printf("\t-dump N\t\t\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n N <champion.cor>\t: Sets champion id to N \n");
	ft_free_gc(A->gc);
	free(A->gc);
	exit(0);
}
