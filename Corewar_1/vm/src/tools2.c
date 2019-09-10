/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:52:43 by abinois           #+#    #+#             */
/*   Updated: 2019/09/10 16:20:20 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

int		check_reg_num(t_param *param, int i)
{
	int		tmp;

	tmp = change_endian(param->value[i]);
	if (tmp < 1 || tmp > 16)
	{
		param->error = 1;
		return (0);
	}
	return (1);
}

void	exit_dump(t_arena *arena)
{
	print_arena(arena);
	ft_free_gc(arena->gc);
	free(arena->gc);
	exit(1);
}

void	ft_error(t_arena *arena, char *message)
{
	ft_free_gc(arena->gc);
	free(arena->gc);
	ft_printf("{red}%s{reset}\n", message);
	exit(EXIT_FAILURE);
}

int		update_pc(int old_pc, int i)
{
	return ((old_pc + i) % MEM_SIZE);
}
