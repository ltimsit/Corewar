/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/02 18:05:38 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_st(t_op op, t_process *process, t_arena *arena)
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
	param.data = elem[0];
	if (param.type[1] == REG_CODE)
		param.dest_pc = -change_endian(param.value[1]);
	if (param.type[1] == IND_CODE)
		param.dest_pc = change_endian(param.value[1]);
	if (!param.data)
		process->carry = 1;
	process->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	if (process->param.type[1] == REG_CODE)
		put_data_in_reg(process, -process->param.dest_pc);
	if (process->param.type[1] == IND_CODE)
		put_param_in_field(arena, process->param, 4, process->param.dest_pc);
	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}
