/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjump.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:53:15 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/12 17:45:31 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_zjump(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	(void)op;
	stock_in_param(A, &param.value[0], 2, update_pc(process->pc, 1));
//	ft_chen((char*)&param.value[0], 2);
	param.data = (short)chen4(param.value[0]) % IDX_MOD;
	process->pc_next = !process->carry ? 3 : param.data;
}

void	execute_zjump(t_process *process, t_arena *arena)
{
	(void)A;
	(void)process;
}
