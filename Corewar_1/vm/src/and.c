/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:35:33 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/13 13:38:35 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Param 1: RG/ID/D4(source)
** Param 2: RG/ID/D4(source)
** Param 3: RG(dest)
*/

void	fc_and(t_op op, t_process *process, t_arena *arena)
{
	t_param		param;
	int			elem[3];
	int			i;

	i = 0;
	param = fill_param(A, op, process, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, process,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, process,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	param.data = elem[0] & elem[1];
	param.dest_pc = param.value[2];
	process->param = param;
}

void	execute_and(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
	process->carry = !process->param.data ? 1 : 0;
}
