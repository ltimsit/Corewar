/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:43:56 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/24 13:26:32 by abinois          ###   ########.fr       */
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

char	*get_line(t_data *data)
{
	int		ret;
	char	*line;

	line = NULL;
	ft_printf("get_line bonjour \n");
	ret = ft_get_next_line(D->fd, &line, 0);
	if (ret == -1 /*|| !ft_add_to_gc(line, &(D->gc), &(D->head_gc))*/)
		return (NULL);
	D->curr_line++;
	return (line);
}

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

int		name_or_comment(t_data *data, char *line, int *end_index)
{
	char	tmp;

	*end_index = skip_nosp(line, 0);
	tmp = line[*end_index];
	line[*end_index] = '\0';
	if (!ft_strcmp(line, NAME_CMD_STRING) && !D->name_set)
	{
		line[*end_index] = tmp;
		D->chmp_name = stock_namecom(line + *end_index);//a proteger
		D->name_set = true;
		ft_printf("name =%s\n", D->chmp_name);
		return (name_line);
	}
	else if (!ft_strcmp(line, COMMENT_CMD_STRING) && !D->comment_set)
	{
		line[*end_index] = tmp;
		D->chmp_com = stock_namecom(line + *end_index);//a proteger
		D->comment_set = true;
		ft_printf("comment =%s\n", D->chmp_com);
		return (comment_line);
	}
	return (get_error(D, syntax));
}

int		define_cmd_type(t_data *data, char *line, int *end_index)
{
//	char	buf[64];
	int		cpt;

	*end_index = skip_nosp(line, 0);
	line[*end_index] = '\0';
	cpt = -1;
	while (++cpt < NB_COMMAND)
		if (!ft_strcmp(line, op_tab[cpt].name))
			return (command_line + cpt);
	cpt = -1;
	while (check_in_label_char(line[++cpt]))
		if (line[cpt] == LABEL_CHAR)
			return (label_line);
	return (get_error(D, lexical));
}

int		manage_lines(t_data *data)
{
	int		j;
	int		type;

	while ((D->line = get_line(D)))
	{
		D->curr_index = skip_sp(D->line, 0);
		if (!D->line[D->curr_index])
			continue ;
		if ((!D->name_set || !D->comment_set)
				&& !(type = name_or_comment(D, D->line + D->curr_index, &j)))
			return (0);
		else if (!(type = define_cmd_type(D, D->line + D->curr_index, &j)))
			return (0);
	}
	return (0);
}
