/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:48:28 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 14:11:21 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**param 1 source  : Index/ Direct 4(number)
**param 2 dest    : Registre
*/

void	fc_ld(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	ft_bzero(elem, sizeof(elem));
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, PRO, elem);
	param.data = param.type[0] == IND_CODE ?
		fill_index_content(A, PRO,
				(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	param.dest_pc = param.value[1];
	PRO->param = param;
}

void	execute_ld(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}

/*
**param 1 source  : Index/ Direct 4(number)
**param 2 dest    : Registre
*/

void	fc_lld(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	ft_bzero(elem, sizeof(elem));
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, PRO, elem);
	param.data = elem[0];
	param.dest_pc = param.value[1];
	PRO->param = param;
}

void	execute_lld(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}
