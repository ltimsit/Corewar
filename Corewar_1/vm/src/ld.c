/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:48:28 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/09 20:36:23 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_ld(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = param.type[0] == T_IND ?
		fill_index_content(arena, process,
				change_endian(param.value[0]) % IDX_MOD): elem[0];
	param.dest_pc = change_endian(param.value[1]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_ld(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}

void	fc_lld(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = elem[0];
	param.dest_pc = change_endian(param.value[1]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_lld(t_process *process, t_arena *arena)
{
	(void)arena;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}
