/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:19:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/10 15:42:01 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_xor(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = 0;
	param = fill_param(arena, op, process, elem);
	elem[0] = param.type[0] == IND_CODE ?
		fill_index_content(arena, process,
				change_endian(param.value[0] % IDX_MOD)) : elem[0];
	elem[1] = param.type[1] == IND_CODE ?
		fill_index_content(arena, process,
				change_endian(param.value[1] % IDX_MOD)) : elem[1];
	param.data = elem[0] ^ elem[1];
	param.dest_pc = change_endian(param.value[2]);
	process->param = param;
}

void	execute_xor(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
	process->carry = !process->param.data ? 1 : 0;
}
