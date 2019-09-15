/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:26:32 by abinois           #+#    #+#             */
/*   Updated: 2019/09/15 17:33:29 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_color_value(unsigned char *carriage, int size, int p_nb)
{
	int i;

	i = -1;
	while (++i < size)
		carriage[i] += (1 << p_nb);
}

void	clear_carriage_superpo(t_arena *arena)
{
	t_process	*tmp;
	int			i;

	tmp = A->p_head;
	i = -1;
	if (A->nb_process < 4096)
	{
		while (tmp)
		{
			if ((A->carriage[tmp->pc] >> 5) & 1)
				A->carriage[tmp->pc] ^= 1 << 5;
			tmp = tmp->next;
		}
	}
	else
		while (++i < MEM_SIZE)
			if ((A->carriage[i] >> 5) & 1)
				A->carriage[tmp->pc] ^= 1 << 5;
}
