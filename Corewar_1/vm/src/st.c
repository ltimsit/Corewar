/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/10 10:37:30 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_st(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	param = fill_param(arena, op, process, elem);
	param.data = elem[0];
	param.dest_pc = param.type[1] == IND_CODE ?
		change_endian(param.value[1] % IDX_MOD) :
		change_endian(param.value[1]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)arena;
	if (process->param.type[1] == REG_CODE)
		put_data_in_reg(process, process->param.data, process->param.dest_pc);
	else if (process->param.type[1] == IND_CODE)
		put_param_in_field(arena, change_endian(process->param.data), 4,
				update_pc(process->pc, process->param.dest_pc));
}
