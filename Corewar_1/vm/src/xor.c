/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:19:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/03 19:24:12 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_xor(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = 0;
	param = fill_param(arena, op, process, elem);
	param.data = elem[0] ^ elem[1];
	param.dest_pc = change_endian(param.value[2]);
	process->carry = param.data ? 0 : 1;
	process->param = param;
}

void	execute_xor(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}