/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:16:38 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 16:01:22 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		skip_sp(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		skip_nosp(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	return (i);
}

int		get_error(t_data *data, int err_type, char *elem)
{
	D->err = err_type;
	print_error(data, elem);
	return (0);
}

void	fill_op_and_err_tab()
{
	err_tab[0] = "lexical error : ";
	err_tab[1] = "syntax error : ";
	err_tab[2] = "read error !";
	err_tab[3] = "param error : ";
	err_tab[4] = "missing coma !";

//	op_tab[0] = {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
/*
	op_tab[1] = {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	op_tab[2] = {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	op_tab[3] = {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0};
	op_tab[4] = {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0};
	op_tab[5] = {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	op_tab[6] = {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	op_tab[7] = {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	op_tab[8] = {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	op_tab[9] = {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1};
	op_tab[10] = {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1};
	op_tab[11] = {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	op_tab[12] = {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0};
	op_tab[13] = {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1};
	op_tab[14] = {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	op_tab[15] = {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
	op_tab[16] = {0, 0, {0}, 0, 0, 0, 0, 0};
	*/
}

/*
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
*/
/*

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
*/
