/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/29 12:54:34 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static t_op	op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int		set_header(t_data *data)
{
	if (!(change_endian(D, (char *)&(D->header.magic), 4))
			|| !(mem_stock(D, D->header.prog_name, PROG_NAME_LENGTH))
			|| !(change_endian(D, (char *)&(D->header.prog_size), 4))
			|| !(mem_stock(D, D->header.comment, COMMENT_LENGTH)))
		return (0);
	return (1);
}

int		get_elem(t_data *data, char *tab, int tab_size, char sep_char)
{
	int i;

	i = 0;
	while (i < tab_size && *D->line != ' ' && *D->line != '\t'
			&& *D->line != '\n')
	{
		if (!*D->line)
		{
			if (!(get_new_read(data)))
				return (0);
			continue ;
		}
		if (sep_char && *D->line == sep_char)
			break;
		tab[i++] = *(D->line)++;
	}
	tab[i] = '\0';
	return (i);
}

int		go_to_next_elem(t_data *data, int *line_id, int *col_id)
{
	int		i;

	if (!D->line && !get_new_read(D))
		return (get_error(D, read_error, NULL));
	while ((i = skip_sp(D->line, 0)) != -1)
	{
		D->line += i;
		if (*(D->line) == '#')
			skip_comment_block(D);
		if (*(D->line) == '\n')
		{
			(*line_id)++;
			*col_id = 0;
			D->line++;
			continue ;
		}
		else if (!(*D->line) && !(get_new_read(D)))
			return (0);
		else
		{
			(*col_id) = (*col_id) + i;
			return (1);
		}
	}
	return (42);
}

int		get_type(t_data *data, char *elem)
{
	int		cpt;

	cpt = -1;
	while (++cpt < NB_COMMAND - 1)
		if (!ft_strcmp(elem, op_tab[cpt].name))
			return (command_line + cpt);
	cpt = -1;
	while (check_in_label_char(elem[++cpt]))
		if (elem[cpt] == LABEL_CHAR)
		{
			elem[cpt] = '\0';
			return (label_line);
		}
	return (get_error(D, syntax, NULL));
}

int		read_and_dispatch(t_data *data)
{
	int		type;
	char	cmd[14];
	int		i;

	while (!D->name_set || !D->comment_set)
	{
		go_to_next_elem(D, &D->curr_line, &D->curr_index);
		i = get_elem(D, cmd, 14, 0);
		if (!ft_strcmp(cmd, NAME_CMD_STRING) && D->name_set)
		{
			D->name_set = true;
			D->curr_index += i;
			fc_namecom(D, D->header.prog_name, PROG_NAME_LENGTH);
		}
		else if (!ft_strcmp(cmd, COMMENT_CMD_STRING) && !D->comment_set)
		{
			D->comment_set = true;
			D->curr_index += i;
			fc_namecom(D, D->header.comment, COMMENT_LENGTH);
		}
		else
		{
			ft_printf("yolo\n");
			return (get_error(D, syntax, cmd));
		}
	}
	set_header(data);
	while (go_to_next_elem(D, &D->curr_line, &D->curr_index))
	{
		i = get_elem(D, cmd, 14, 0);
		type = get_type(D, cmd);
		D->curr_index += i;
		ft_printf("{blue}pc = %d elem = \"%s\"{reset} | {yellow}type = %d\n{reset}", D->pc, cmd, type);
		if (type == 3)
			add_to_label_list(D, cmd, D->pc);
		if (type > 3)
			if (!(fc_cmd(D, type, op_tab[type - command_line])))
				return (0);
		ft_printf("{cyan}-- boucle --{reset}\n");
	}
	fill_missing_label(D);
	return (1);
}
