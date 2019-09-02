/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:35:33 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/02 14:41:19 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_and(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[2];
	int i;

	i = 0;
	param = fill_param(arena, op, process);
	while (++i < 2)
	{
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i])];
		if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param, i);
	}
	param.data = elem[0] & elem[1];
	param.dest_pc = -change_endian(param.value[2]);
	process->carry = param.data ? 0 : 1;
	process->param = param;
	ft_printf("{cyan}data = %d{reset}\n", param.data);
	ft_printf("param 1 :%.2x , param 2:%.2x , param 3:%.2x , dest :%.2x\n", param.value[0]
			, param.value[1], param.value[2], param.dest_pc);
}

void	execute_and(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	put_data_in_reg(process, change_endian(process->param.value[2]));
	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}
