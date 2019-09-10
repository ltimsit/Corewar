/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:16:32 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/10 15:06:33 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_add(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = elem[0] + elem[1];
	param.dest_pc = change_endian(param.value[2]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_add(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}
