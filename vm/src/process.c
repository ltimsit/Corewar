/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/19 18:04:01 by ltimsit-         ###   ########.fr       */
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
		check_process(A, tmp);
		tmp = tmp->next;
	}
	clear_carriage_superpo(arena);
}

int		verif_process(t_arena *arena, t_process *head)
{
	t_process	*tmp;
	int			nb_live;
	t_process	*prev;
	t_process	*todel;

	prev = NULL;
	tmp = head;
	nb_live = 0;
	while (tmp)
	{
		if (!tmp->nb_live)
		{
			todel = tmp;
			tmp = tmp->next;
			del_process(A, todel, prev);
		}
		else
		{
			nb_live += tmp->nb_live;
			tmp->nb_live = 0;
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (nb_live);
}

void	init_process(t_process *process, int id_champ, int player_nb)
{
	PRO->reg[0] = id_champ;
	PRO->id_champ = id_champ;
	PRO->player_nb = player_nb;
}

void	add_process(t_arena *arena, int id_champ, int player_nb)
{
	t_process *new_process;

	if (!(new_process = ft_memalloc(sizeof(t_process))))
	{
		free_l_process(A);
		ft_error(A, "Malloc error\n");
	}
	if (!(A->p_head))
	{
		A->p_head = new_process;
		A->PRO = new_process;
	}
	else
	{
		A->PRO->next = new_process;
		A->PRO = new_process;
	}
	A->nb_process++;
	init_process(A->PRO, id_champ, player_nb);
}

void	del_process(t_arena *arena, t_process *todel, t_process *prev)
{
	if (!prev)
		A->p_head = A->p_head->next;
	else
		prev->next = todel->next;
	if ((A->carriage[todel->pc] >> 4) & 1)
		A->carriage[todel->pc] ^= 1 << 4;
	ft_memdel((void **)&todel, 0);
	A->nb_process--;
}
