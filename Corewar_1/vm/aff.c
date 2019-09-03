/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:04:22 by abinois           #+#    #+#             */
/*   Updated: 2019/09/03 17:17:27 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_aff(t_op op, t_process *process, t_arena *arena)
{
	t_param param;

	process->c_todo = op.time;
	process->pc_next = 2;
	stock_in_param(arena, &param.value[0], 1, update_pc(process->pc, 1));
	param.data = param->reg[change_endian(param.value[0])] % 256;
	process->carry = !param.data ? 1 : 0;
}

void	execute_aff(t_process *process, t_arena *arena)
{
	(void)arena;
	(void)process;
}
