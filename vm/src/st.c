/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 14:12:42 by avanhers         ###   ########.fr       */
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

	ft_bzero(elem, sizeof(elem));
	param = fill_param(A, op, PRO, elem);
	param.data = elem[0];
	param.dest_pc = param.type[1] == IND_CODE ?
		chen4((short)chen4(param.value[1]) % IDX_MOD) : param.value[1];
	PRO->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)A;
	if (PRO->param.type[1] == REG_CODE)
		put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	else if (PRO->param.type[1] == IND_CODE)
		put_param_in_field(A, PRO, 4);
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
	int		tmp;

	ft_bzero(elem, sizeof(elem));
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, PRO, elem);
	param.data = elem[0];
	elem[2] = param.type[2] == IND_CODE ? chen4(fill_index_content(A, PRO,
				chen4(param.value[2]) % IDX_MOD)) : chen4(elem[2]);
	elem[1] = param.type[1] == IND_CODE ? chen4(fill_index_content(A, PRO,
				chen4(param.value[1]) % IDX_MOD)) : chen4(elem[1]);
	tmp = ((short)elem[1] + (short)elem[2]) % IDX_MOD;
	param.dest_pc = chen4(tmp);
	PRO->param = param;
}

void	execute_sti(t_process *process, t_arena *arena)
{
	put_param_in_field(A, PRO, 4);
}
