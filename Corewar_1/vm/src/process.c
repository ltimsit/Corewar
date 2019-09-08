/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/08 15:51:51 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_process(t_process *process)
{
	ft_printf("\n {green}PC = %d{reset}", process->pc);
	ft_printf("\n {blue}Carry = %d{reset}", process->carry);
	ft_printf("\n {yellow}Nb_Live = %d{reset}", process->nb_live);
	ft_printf("\n {red}id_champ =  %d{reset}\n", process->id_champ);
}

void	init_process(t_process *process, int id_champ)
{
	process->reg[0] = id_champ;
	process->id_champ = id_champ;
}

void	add_process(t_arena *arena, int id_champ)
{
	t_process *new_process;

	if (!(new_process = ft_alloc_gc(1, sizeof(t_process), arena->gc)))
		ft_error("Malloc error\n");
	ft_bzero(new_process, sizeof(t_process));
	if (!(arena->p_head))
	{
		arena->p_head = new_process;
		arena->process = new_process;
	}
	else
	{
		arena->process->next = new_process;
		arena->process = new_process;
	}
	init_process(arena->process, id_champ);
}

void	del_process(t_arena *arena, t_process *todel, t_process *prev)
{
	if (!prev)
		arena->p_head = arena->p_head->next;
	else
		prev->next = todel->next;
}
