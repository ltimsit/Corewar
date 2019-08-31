/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:40:52 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/31 17:32:18 by avanhers         ###   ########.fr       */
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
	process->nb_live = 0;
}



void	add_process(t_arena *arena, int id_champ)
{
	t_process *new_process;

	if (!(new_process = ft_alloc_gc(1, sizeof(t_process), arena->gc)))
		ft_error("Malloc error\n");
	if (!(arena->champ[id_champ].p_head))
	{
		arena->champ[id_champ].p_head = new_process;
		arena->champ[id_champ].process = new_process;
	}
	else
	{
		arena->champ[id_champ].process->next = new_process;
		arena->champ[id_champ].process = new_process;
	}
	ft_bzero(new_process, sizeof(t_process));
}	
