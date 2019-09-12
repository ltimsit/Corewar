/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:30:58 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 12:11:45 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** D4 (id du joueur)
*/
char	*check_valid_champ(int id, t_arena *arena)
{
	int		i;

	i = -1;
	while (++i < A->nb_champ)
		if (A->champ[i].id == id)
			return (A->champ[i].h.prog_name);
	return (NULL);
}

void	fc_live(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	(void)op;
	ft_bzero(&param, sizeof(t_param));
	process->pc_next = 5;
	stock_in_param(A, &param.value[0], 4, update_pc(process->pc, 1));
	param.data = chen4(param.value[0]);
	process->param = param;
}

void	execute_live(t_process *process, t_arena *arena)
{
	char	*name;

	(void)A;
	(void)process;
	process->nb_live += 1;
	if (!(name = check_valid_champ(process->param.data, A)))
		return ;
	A->last_living_champ = process->param.data;
	ft_printf("Un processus dit que le joueur %s est en vie.\n", name);
}

void	fc_aff(t_op op, t_process *process, t_arena *arena)
{
	t_param param;

	(void)op;
	process->pc_next = 2;
	stock_in_param(A, &param.value[0], 1, update_pc(process->pc, 1));
	param.data = chen4(param.value[0]) % 256;
	process->param = param;
}

void	execute_aff(t_process *process, t_arena *arena)
{
	(void)A;
	(void)process;
	if (process->aff_index == AFF_SIZE || !process->param.data)
	{
		ft_printf("{purple}%s\n", process->aff);
		process->aff_index = 0;
		ft_bzero(process->aff, AFF_SIZE);
	}
	else
		process->aff[process->aff_index++] = process->param.data;
	process->carry = !process->param.data ? 1 : 0;
}
