/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:34:46 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/08 15:52:59 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process, elem);
	param.data = elem[0];
	param.dest_pc = update_pc(process->pc, elem[1] + elem[2]);
	process->param = param;
}

void	execute_sti(t_process *process, t_arena *arena)
{
	put_param_in_field(arena, process->param.data, 4, process->param.dest_pc);
}
