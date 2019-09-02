/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:12:18 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/02 18:07:14 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_sub(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process);
	while (++i < 2)
	{
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i]) - 1];
		else if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		else if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param.value[i]);
	}
	param.data = elem[0] - elem[1];
	param.dest_pc = -change_endian(param.value[2]);
	if (!param.data)
		process->carry = 1;
	process->param = param;
}

void	execute_sub(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	put_data_in_reg(process, -process->param.dest_pc);
	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}
