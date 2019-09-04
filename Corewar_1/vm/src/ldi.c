/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:22:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/03 15:40:37 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_ldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = fill_index_content(arena, process, elem[0] + elem[1]);
	param.dest_pc = change_endian(param.value[2]);
	process->carry = !param.data ? 1 : 0;
	process->param = param;
}

void	execute_ldi(t_process *process, t_arena *arena)
{
	(void)arena;
//	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
//	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}

void	fc_lldi(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

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
//	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
//	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
}
