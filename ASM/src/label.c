/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:16:33 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/18 15:02:15 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		add_to_label_instr(t_data *data, char *elem, int mem_index, int size)
{
	t_label_instr *label_new;

	if (!(label_new = ft_alloc_gc(1, sizeof(t_label_instr), D->gc)))
		get_error(D, malloc_err, NULL);
	ft_bzero(label_new, sizeof(t_label_instr));
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		get_error(D, malloc_err, NULL);
	label_new->mem_index = mem_index;
	label_new->pc = D->pc;
	label_new->size = size == 0 ? 4 : 2;
	label_new->line = D->curr_line;
	label_new->col = D->curr_index;
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
	ft_bzero(label_new, sizeof(t_label_add));
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		return (0);
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
		val = 0xFFFF + label_pc - curr_pc + 1;
	else
		val = 0xFFFF + (label_pc - curr_pc + 1);
	return ((int)val);
}

int		put_add_in_mem_stock(t_data *data, int mem_index, int add, int size)
{
	if (size == 4)
	{
		D->mem_stock[mem_index] = ((char *)&add)[3];
		D->mem_stock[mem_index + 1] = ((char *)&add)[2];
		D->mem_stock[mem_index + 2] = ((char *)&add)[1];
		D->mem_stock[mem_index + 3] = ((char *)&add)[0];
	}
	else
	{
		D->mem_stock[mem_index] = ((char *)&add)[1];
		D->mem_stock[mem_index + 1] = ((char *)&add)[0];
	}
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
						(short)calc_val_from_pc(tmp->pc, tmp2->pc), tmp->size);
			tmp2 = tmp2->next;
		}
		if (!i)
			get_error_label(D, tmp, tmp->name);
		tmp = tmp->next;
	}
	return (1);
}
