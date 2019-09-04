/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:30:58 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/03 17:17:32 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_live(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	process->c_todo = op.time;
	process->pc_next = 5;
	stock_in_param(arena, &param.value[0], 4, update_pc(process->pc, 1));
	param.data = change_endian(param.value[0]);
}

void	execute_live(t_process *process, t_arena *arena)
{
	(void)arena;
	(void)process;
//	ft_printf("le joueur {blue}%s[%d]{reset} a ete declare en vie !\n", "banane", process->param.data);
}
