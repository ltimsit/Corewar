/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/02 16:07:23 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"

void	print_process(t_champ *champ)
{
	t_process	*tmp;
	int 		i;
	
	tmp = champ->p_head;
	ft_printf("{under}{rev}Champion : %s\n{reset}", champ->h.prog_name);
	while (tmp)
	{
		i = -1;
		while (++i < REG_NUMBER)
			ft_printf("R%d[%.4d] ", i + 1, tmp->reg[i]);
		ft_printf("\n {green}PC = %d{reset}", tmp->pc);
		ft_printf("\n {blue}carry = %d{reset}", tmp->carry);
		ft_printf("\n {yellow}nb_live = %d{reset}", tmp->nb_live);
		ft_printf("\n {red}alive =  %d{reset}\n", tmp->alive);
		tmp = tmp->next;
	}
}

void	init_process(t_process *process, int id_champ)
{
	process->reg[0] = id_champ;
	process->alive = 1;
}



void	add_process(t_arena *arena, int pos)
{
	t_process *new_process;

	if (!(new_process = ft_alloc_gc(1, sizeof(t_process), arena->gc)))
		ft_error("Malloc error\n");
	ft_bzero(new_process, sizeof(t_process));
	if (!(arena->champ[pos].p_head))
	{
		arena->champ[pos].p_head = new_process;
		arena->champ[pos].process = new_process;
	}
	else
	{
		arena->champ[pos].process->next = new_process;
		arena->champ[pos].process = new_process;
	}
}	
