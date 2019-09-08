/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:35:33 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/03 16:00:07 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_and(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = 0;
	param = fill_param(arena, op, process, elem);
	param.data = elem[0] & elem[1];
	param.dest_pc = change_endian(param.value[2]);
	process->carry = param.data ? 0 : 1;
	process->param = param;
}

void	execute_and(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}