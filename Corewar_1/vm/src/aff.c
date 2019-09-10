/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:04:22 by abinois           #+#    #+#             */
/*   Updated: 2019/09/10 15:33:54 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_aff(t_op op, t_process *process, t_arena *arena)
{
	t_param param;

	process->c_todo = op.time;
	process->pc_next = 2;
	stock_in_param(arena, &param.value[0], 1, update_pc(process->pc, 1));
	param.data = process->reg[change_endian(param.value[0])] % 256;
	process->param = param;
}

void	execute_aff(t_process *process, t_arena *arena)
{
	(void)arena;
	(void)process;
	if (process->aff_index == AFF_SIZE || !process->param.data)
	{
		ft_printf("{purple}%s\n", process->aff);
		ft_bzero(process->aff, AFF_SIZE);
	}
	else
		process->aff[process->aff_index++] = process->param.data;
	process->carry = !process->param.data ? 1 : 0;
}
