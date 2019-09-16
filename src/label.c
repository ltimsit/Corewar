/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:16:33 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/11 14:12:44 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		add_to_label_instr(t_data *data, char *elem, int mem_index)
{
	t_label_instr *label_new;

	if (!(label_new = ft_alloc_gc(1, sizeof(t_label_instr), D->gc)))
		get_error(D, malloc_err, NULL);
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		get_error(D, malloc_err, NULL);
	label_new->next = NULL;
	label_new->mem_index = mem_index;
	label_new->pc = D->pc;
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

int		add_to_label_list(t_data *data, char *elem, int pc)
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

int		calc_val_from_pc(int curr_pc, int label_pc)
{
	short val;

	if (label_pc >= curr_pc)
		val = 0x0000 + ((short)label_pc - (short)curr_pc);
	else
		val = 0xFFFF + (label_pc - curr_pc + 1);
	return ((int)val);
}

int		put_add_in_mem_stock(t_data *data, int mem_index, int add)
{
	D->mem_stock[mem_index] = ((char *)&add)[1];
	D->mem_stock[mem_index + 1] = ((char *)&add)[0];
	return (1);
}

int		fill_missing_label(t_data *data)
{
	t_label_instr	*tmp;
	t_label_add		*tmp2;
	int				i;

	tmp = D->label->head_instr;
	while (tmp)
	{
		i = 0;
		tmp2 = D->label->head_add;
		while (tmp2)
		{
			if (!ft_strcmp(tmp->name, tmp2->name))
				i = put_add_in_mem_stock(D, tmp->mem_index,
						calc_val_from_pc(tmp->pc, tmp2->pc));
			tmp2 = tmp2->next;
		}
		if (!i)
			get_error(D, syntax, tmp->name);
		tmp = tmp->next;
	}
	return (1);
}
