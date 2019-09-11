/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:58:41 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/11 14:52:55 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_st(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	param = fill_param(arena, op, process, elem);
	param.data = elem[0];
	elem[1] = param.type[1] == IND_CODE ? 
		(short)change_endian(param.value[1]) % IDX_MOD :
		change_endian(param.value[1]);
	param.dest_pc = param.type[1] == IND_CODE ? update_pc(elem[1], process->pc)
	   	: elem[1];
	process->param = param;
}

void	execute_st(t_process *process, t_arena *arena)
{
	(void)arena;
	if (process->param.type[1] == REG_CODE)
		put_data_in_reg(process, process->param.data, process->param.dest_pc);
	else if (process->param.type[1] == IND_CODE)
		put_param_in_field(arena, change_endian(process->param.data), 4, process->param.dest_pc);
	process->carry = !process->param.data ? 1 : 0;
}

void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;
	int		tmp;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	elem[2] = param.type[2] == IND_CODE ?
		(short)change_endian(param.value[2]) % IDX_MOD : elem[2];
	elem[1] = param.type[1] == IND_CODE ?
		(short)change_endian(param.value[1]) % IDX_MOD : elem[1];
	param.data = change_endian(elem[0]);
	tmp = (short)(elem[1] + elem[2]) % IDX_MOD;
	param.dest_pc = update_pc(process->pc, tmp);
	process->param = param;
}

void	execute_sti(t_process *process, t_arena *arena)
{
	put_param_in_field(arena, process->param.data, 4, process->param.dest_pc);
	process->carry = !process->param.data ? 1 : 0;
}
