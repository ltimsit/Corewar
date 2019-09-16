/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:29:51 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/16 13:56:06 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**  D2(dest of son process)
*/

void	fc_fork(t_op op, t_process *process, t_arena *arena)
{
	t_param param;

	ft_bzero(&param, sizeof(t_param));
	process->c_todo = op.time;
	process->pc_next = 3;
	stock_in_param(A, &param.value[0], 2, update_pc(process->pc, 1));
	param.data = (short)chen4(param.value[0]) % IDX_MOD;
	process->param = param;
}

void	execute_fork(t_process *process, t_arena *arena)
{
	t_process *new_process;

	if (!(new_process = ft_memalloc(sizeof(t_process))))
		ft_error(A, "Malloc error\n");
	new_process->pc = update_pc(process->pc, process->param.data);
	new_process->carry = process->carry;
	new_process->nb_live = process->nb_live;
	new_process->id_champ = process->id_champ;
	new_process->player_nb = process->player_nb;
	ft_memcpy(new_process->reg, process->reg, sizeof(process->reg));
	new_process->next = A->p_head;
	A->p_head = new_process;
	A->carriage[new_process->pc] |= 1 << 4;
	A->nb_process++;
}

void	fc_lfork(t_op op, t_process *process, t_arena *arena)
{
	t_param param;

	ft_bzero(&param, sizeof(t_param));
	process->c_todo = op.time;
	process->pc_next = 3;
	stock_in_param(A, &param.value[0], 2, update_pc(process->pc, 1));
	param.data = chen4(param.value[0]);
	process->param = param;
}

void	execute_lfork(t_process *process, t_arena *arena)
{
	t_process *new_process;

	if (!(new_process = ft_memalloc(sizeof(t_process))))
		ft_error(A, "Malloc error\n");
	new_process->pc = update_pc(process->pc, process->param.data);
	new_process->carry = process->carry;
	new_process->nb_live = process->nb_live;
	new_process->id_champ = process->id_champ;
	new_process->player_nb = process->player_nb;
	ft_memcpy(new_process->reg, process->reg, sizeof(process->reg));
	new_process->next = A->p_head;
	A->p_head = new_process;
	A->carriage[new_process->pc] |= 1 << 4;
	A->nb_process++;
}
