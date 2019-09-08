/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:30:58 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/05 13:19:51 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*check_valid_champ(int id, t_arena *arena)
{
	int		i;

	i = -1;
	while (++i < arena->nb_champ)
		if (arena->champ[i].id == id)
			return (arena->champ[i].h.prog_name);
	return (NULL);
}

void	fc_live(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	process->c_todo = op.time;
	process->pc_next = 5;
	stock_in_param(arena, &param.value[0], 4, update_pc(process->pc, 1));
	param.data = change_endian(param.value[0]);
	process->param = param;
}

void	execute_live(t_process *process, t_arena *arena)
{
	char	*name;

	(void)arena;
	(void)process;
	process->nb_live += 1;
	if (!(name = check_valid_champ(process->param.data, arena)))
		return ;
	arena->last_living_champ = process->param.data;
	ft_printf("Un processus dit que le joueur %s est en vie.\n", name);
}