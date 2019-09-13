/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/13 08:49:25 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Param 1  source : Registre
** Param 2  dest   : Registre, Index
*/

void	fc_st(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	param = fill_param(A, op, process, elem);
	param.data = elem[0];
	param.dest_pc = param.type[1] == IND_CODE ?
		chen4((short)chen4(param.value[1]) % IDX_MOD) : param.value[1];
	process->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)A;
	if (process->param.type[1] == REG_CODE)
		put_data_in_reg(process, process->param.data, process->param.dest_pc);
	else if (process->param.type[1] == IND_CODE)
		put_param_in_field(A, process, 4);
	process->carry = !process->param.data ? 1 : 0;
}

/*
** Param 1  source : Registre
** Param 2  source : Registre, Index, Direct 2
** Param 3  source : Index, Direct 2
*/

void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;
	int		tmp;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, process, elem);
	param.data = elem[0];
	elem[2] = param.type[2] == IND_CODE ? chen4(fill_index_content(A, process,
				chen4(param.value[2]) % IDX_MOD)) : chen4(elem[2]);
	elem[1] = param.type[1] == IND_CODE ? chen4(fill_index_content(A, process,
				chen4(param.value[1]) % IDX_MOD)) : chen4(elem[1]);
	tmp = ((short)elem[1] + (short)elem[2]) % IDX_MOD;
	param.dest_pc = chen4(tmp);
	process->param = param;
}

void	execute_sti(t_process *process, t_arena *arena)
{
	put_param_in_field(A, process, 4);
}
