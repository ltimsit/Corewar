/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:16:33 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 14:17:31 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		add_to_label_instr(t_data *D, char *elem, int mem_index)
{
	 t_label_instr *label_new;

	 if (!(label_new = ft_alloc_gc(1, sizeof(t_label_instr), D->gc)))
	  	return (0);
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		 	return (0);
	label_new->next = NULL;
	label_new->mem_index = mem_index;
	 if (!(D->label->lst_instr))
	 {
		 D->label->lst_instr = label_new;
		 D->label->head_instr = label_new;
	 }
	 else
	 {
		 D->label->lst_instr->next = label_new;
		 D->label->lst_instr = label_new;
	 }
		return (1);
}

int		add_to_label_list(t_data *D, char *elem, int pc)
{
	 t_label_add *label_new;

	 if (!(label_new = ft_alloc_gc(1, sizeof(t_label_add), D->gc)))
	  	return (0);
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		 	return (0);
	label_new->next = NULL;
	label_new->pc = pc;
	 if (!(D->label->lst_add))
	 {
		 D->label->lst_add = label_new;
		 D->label->head_add = label_new;
	 }
	 else
	 {
		 D->label->lst_add->next = label_new;
		 D->label->lst_add = label_new;
	 }
		return (1);
}

int		check_label(t_data *data, char *elem)
{
	t_label_add *tmp;

	tmp = D->label->head_add;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, elem))
			return (tmp->pc);
		tmp = tmp->next;
	}
	return (-1);
}
