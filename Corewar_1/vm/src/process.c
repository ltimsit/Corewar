/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/13 16:15:16 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

void	process_process(t_arena *arena)
{
	t_process *tmp;

	tmp = A->p_head;
	while (tmp)
	{
		if (A->total_cycle == 4550 && tmp->pc == 69 )
		{
			ft_printf(" add :%p carry : %d, pc->next : %d, done :%d\n", &tmp, tmp->carry, tmp->pc_next,tmp->c_done);
		}
		check_process(A, tmp);
		tmp = tmp->next;
	}
}

int		verif_process(t_arena *arena, t_process *head)
{
	t_process	*tmp;
	int			nb_live;
	t_process	*prev;

	prev = NULL;
	tmp = head;
	nb_live = 0;
	while (tmp)
	{
		if (!tmp->nb_live)
			del_process(A, tmp, prev);
		else
		{
			nb_live += tmp->nb_live;
			tmp->nb_live = 0;
			prev = tmp;
		}
		tmp = tmp->next;
	}
	return (nb_live);
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
