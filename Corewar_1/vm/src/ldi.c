/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:22:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/10 10:37:49 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_ldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	elem[0] = param.type[0] == IND_CODE ?
		change_endian(param.value[0] % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ?
		change_endian(param.value[1] % IDX_MOD) : elem[1];
	param.data = fill_index_content(arena, process, elem[0] + elem[1]);
	param.dest_pc = change_endian(param.value[2]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_ldi(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}

void	fc_lldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = fill_index_content(arena, process, elem[0] + elem[1]);
	param.dest_pc = change_endian(param.value[2]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_lldi(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}
