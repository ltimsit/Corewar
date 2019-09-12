/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 10:20:51 by abinois          ###   ########.fr       */
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

void	init_process(t_process *process, int id_champ, int player_nb)
{
	process->reg[0] = id_champ;
	process->id_champ = id_champ;
	process->player_nb = player_nb;
}

void	add_process(t_arena *arena, int id_champ, int player_nb)
{
	t_process *new_process;

	if (!(new_process = ft_alloc_gc(1, sizeof(t_process), A->gc)))
		ft_error(A, "Malloc error\n");
	ft_bzero(new_process, sizeof(t_process));
	if (!(A->p_head))
	{
		A->p_head = new_process;
		A->process = new_process;
	}
	else
	{
		A->process->next = new_process;
		A->process = new_process;
	}
	init_process(A->process, id_champ, player_nb);
}

void	del_process(t_arena *arena, t_process *todel, t_process *prev)
{
	if (!prev)
		A->p_head = A->p_head->next;
	else
		prev->next = todel->next;
}
