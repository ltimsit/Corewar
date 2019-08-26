/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/26 18:13:37 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "unistd.h"

int		set_header(t_data *data)
{
	if (!(put_header(data, D->header.magic))
			|| !(mem_stock(D, D->header.prog_name, PROG_NAME_LENGTH))
			|| !(put_header(data, D->header.prog_size))
			|| !(mem_stock(D, D->header.comment, COMMENT_LENGTH)))
		return (0);
	return (1);
}

int		get_new_read(t_data *data)
{
	int		ret;

	ret = 0;
	if (!D->line
			&& !(D->line = ft_alloc_gc(READSIZE + 1, sizeof(char), D->gc)))
		return (0);
	if ((ret = read(D->fd, D->line, READSIZE)) == -1)
		return (get_error(D, read_error));
	D->line[ret] = '\0';
	return (1);
}

int		get_elem(t_data *data, char *tab, int tab_size)
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
		tab[i++] = *(D->line)++;
	}
	tab[i] = '\0';
	return (i);
}

int		get_to_next_elem(t_data *data, int *line_id, int *col_id)
{
	int		i;

	if (!D->line && !get_new_read(D))
		return (get_error(D, read_error));
	while ((i = skip_sp(D->line, 0)) != -1)
	{
		D->line += i;
		if (*(D->line) == '\n')
		{
			(*line_id)++;
			*col_id = 0;
			D->line++;
			continue ;
		}
		else if (!*(D->line))
		{
			if (!(get_new_read(D)))
				return (0);
		}
		else
		{
			(*col_id) = (*col_id) + i;
			return (1);
		}
	}
	return (42);
}

int		read_and_dispatch(t_data *data)
{
//	int		type;
	char	cmd[14];

	while (!D->name_set || !D->comment_set)
	{
		get_to_next_elem(D, &D->curr_line, &D->curr_index);
		get_elem(D, cmd, 14);
		if (!ft_strcmp(cmd, NAME_CMD_STRING) && (D->name_set = true))
			fc_namecom(D, D->header.prog_name, PROG_NAME_LENGTH);
		else if (!ft_strcmp(cmd, COMMENT_CMD_STRING) && (D->comment_set = true))
			fc_namecom(D, D->header.comment, COMMENT_LENGTH);
	}
	ft_printf("%s\n\n%s", D->header.prog_name, D->header.comment);
	while (get_to_next_elem(D, &D->curr_line, &D->curr_index))
	{
//		get_elem(D, cmd, 14);
//		type = get_type(D);
//		if (!(g_fct_tab[type](D, type, D->curr_index)))
//		return (0);
	}
	return (1);
}
