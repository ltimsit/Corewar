/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:19:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/02 18:15:17 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_xor(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = 0;
	param = fill_param(arena, op, process);
	while (++i < 3)
	{
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i])];
		if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param.value[i]);
	}
	param.data = elem[0] ^ elem[1];
	param.dest_pc = -change_endian(param.value[2]);
	process->carry = param.data ? 0 : 1;
	process->param = param;
	ft_printf("{cyan}data = %d{reset}\n", param.data);
	ft_printf("param 1 :%.2x , param 2:%.2x , param 3:%.2x , dest :%.2x\n", param.value[0]
			, param.value[1], param.value[2], param.dest_pc);
}

void	execute_xor(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
//	put_data_in_reg(process, change_endian(process->param.value[2]));
	put_data_in_reg(process, -process->param.dest_pc);
	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}
