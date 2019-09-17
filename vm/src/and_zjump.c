/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_zjump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:53:15 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 10:26:31 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_zjump(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	(void)op;
	stock_in_param(A, &param.value[0], 2, update_pc(PRO->pc, 1));
	param.data = (short)chen4(param.value[0]) % IDX_MOD;
	if (param.data < 0)
		param.data += MEM_SIZE;
	PRO->pc_next = !PRO->carry ? 3 : param.data;
}

void	execute_zjump(t_process *process, t_arena *arena)
{
	(void)A;
	(void)PRO;
}

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
	param = fill_param(A, op, PRO, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	param.data = elem[0] & elem[1];
	param.dest_pc = param.value[2];
	PRO->param = param;
}

void	execute_and(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}
