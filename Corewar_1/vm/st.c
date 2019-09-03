/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/03 19:43:55 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_st(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = -1;
	param = fill_param(arena, op, process, elem);
	param.data = elem[0];
	param.dest_pc = change_endian(param.value[1]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)arena;
	if (process->param.type[1] == REG_CODE)
		put_data_in_reg(process, process->param.data, process->param.dest_pc);
	if (process->param.type[1] == IND_CODE)
	{
		put_param_in_field(arena, change_endian(process->param.data), 4, update_pc(process->pc, process->param.dest_pc));
		n_print_op_exec(update_pc(process->pc, process->param.dest_pc), 4, arena);
	}
	ft_printf("{cyan}process = %p{reset}\n", process);
	ft_printf("{cyan}process n  = %p{reset}\n", process->next);
}
