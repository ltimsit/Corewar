/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:01:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/09 20:31:55 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	stock_in_param(t_arena *arena, int *param, int size, int pc)
{
	int		id_start;
	char	*param_c;

	param_c = (char *)param;
	id_start = 4 - size;
	while (id_start < 4)
	{
		param_c[id_start++] = arena->field[pc++];
		pc %= MEM_SIZE;
	}
}

void	put_param_in_field(t_arena *arena, int param, int size, int pc)
{
	int		id_start;
	char	*param_c;

	param_c = (char *)&param;
	id_start = 4 - size;
	while (id_start < 4)
	{
		arena->field[pc++] = param_c[id_start++];
		pc %= MEM_SIZE;
	}
}

int		fill_index_content(t_arena *arena, t_process *process, int value)
{
	int index;
	int	elem;
	int j;

	j = -1;
	index = update_pc(process->pc, value);
	while (++j < 4)
	{
		((char *)&elem)[j] = arena->field[index++];
		index %= MEM_SIZE;
	}
	return (elem);
}

void	put_data_in_reg(t_process *process, int data, int reg_nb)
{
	reg_nb -= 1;
	if (reg_nb > -1 && reg_nb < 16)
		process->reg[reg_nb] = data;
}
