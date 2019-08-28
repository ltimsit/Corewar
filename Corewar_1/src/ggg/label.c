/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:16:33 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 18:03:08 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		check_in_label_char(char letter)
{
	int		i;
	char	*label_chars;

	label_chars = LABEL_CHARS;
	i = -1;
	while (label_chars[++i])
		if (letter == label_chars[i] || letter == LABEL_CHAR)
			return (1);
	return (0);
}

int		add_to_label_instr(t_data *data, char *elem, int mem_index)
{
	 t_label_instr *label_new;

	 if (!(label_new = ft_alloc_gc(1, sizeof(t_label_instr), D->gc)))
	  	return (0);
	if (!(ft_add_to_gc((label_new->name = ft_strdup(elem)), D->gc)))
		 	return (0);
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
		val = (short)label_pc - (short)curr_pc;
	else
		val = 0xFFFF + (label_pc - curr_pc + 1);
	return ((int)val);
}

int		check_label(t_data *data, char *elem)
{
	t_label_add *tmp;

	tmp = D->label->head_add;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, elem))
			return (calc_val_from_pc(D->pc, tmp->pc));
		tmp = tmp->next;
	}
	return (-1);
}

int		put_add_in_mem_stock(t_data *data, int mem_index, int add)
{
	mem_stock[mem_index] = ((char *)&add[1]);
	mem_stock[mem_index + 1] = ((char *)&add[0]);
	return (1);
}

int		fill_missing_label(t_data *data)
{
	t_label_add *tmp;
	t_label_instr *tmp2;

	tmp = D->label->head_instr;
	while (tmp)
	{
		tmp2 = D->label->head_add;
		while (tmp2)
		{
			if (!ft_strcmp(tmp->name, tmp2->name))
				return (put_add_in_mem_stock(D, tmp->mem_index, calc_val_from_pc(tmp->pc, tmp2->pc)));
			tmp2 = tmp2->next
		}
		tmp = tmp->next;
	}
	return (0);
}