/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:22:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 10:31:31 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**param 1 source  : Reg/Index/ Direct 2
**param 2 source  : Index/D2
**param 3 dest    : Reg
*/

void	fc_ldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		tmp;

	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, PRO, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	tmp = ((short)chen4(elem[0]) + (short)chen4(elem[1])) % IDX_MOD;
	param.data = fill_index_content(A, PRO, tmp);
	param.dest_pc = param.value[2];
	PRO->param = param;
}

void	execute_ldi(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
}

void	fc_lldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, PRO, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	param.data = fill_index_content(A, PRO, chen4(elem[0] + elem[1]));
	param.dest_pc = param.value[2];
	PRO->param = param;
}

void	execute_lldi(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}
