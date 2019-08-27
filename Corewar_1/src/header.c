/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/27 19:55:15 by ltimsit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "unistd.h"

int		set_header(t_data *data)
{
	if (!(change_endian(D, D->header.magic))
			|| !(mem_stock(D, D->header.prog_name, PROG_NAME_LENGTH))
			|| !(change_endian(D, D->header.prog_size))
			|| !(mem_stock(D, D->header.comment, COMMENT_LENGTH)))
		return (0);
	return (1);
}

int		get_new_read(t_data *data)
{
	int		ret;

	ret = 0;
	if (!D->start
			&& !(D->start = ft_alloc_gc(READSIZE + 1, sizeof(char), D->gc)))
		return (0);
	if ((ret = read(D->fd, D->start, READSIZE)) == -1)
		return (get_error(D, read_error, NULL));
	D->start[ret] = '\0';
	D->line = D->start;
	return (ret ? 1 : 0);
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
		{
			D->line++;
			break;
		}
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
	int		type;
	char	cmd[14];
	int		i;

	while (!D->name_set || !D->comment_set)
	{
		go_to_next_elem(D, &D->curr_line, &D->curr_index);
		i = get_elem(D, cmd, 14, 0);
		if (!ft_strcmp(cmd, NAME_CMD_STRING) && (D->name_set = true))
		{
			D->curr_index += i;
			fc_namecom(D, D->header.prog_name, PROG_NAME_LENGTH);
		}
		else if (!ft_strcmp(cmd, COMMENT_CMD_STRING) && (D->comment_set = true))
		{
			D->curr_index += i;
			fc_namecom(D, D->header.comment, COMMENT_LENGTH);
		}
		else
			return (get_error(D, syntax, cmd));
	}
//	ft_printf("%s\n\n%s", D->header.prog_name, D->header.comment);
	set_header(data);
	while (go_to_next_elem(D, &D->curr_line, &D->curr_index))
	{
		i = get_elem(D, cmd, 14, 0);
		ft_printf("elem=%s\n", cmd);
		type = get_type(D, cmd);
		D->curr_index += i;
		ft_printf("type=%d\n", type);
		if (type > 3)
			if (!(g_fct_tab[type](D, type, D->curr_index)))
				return (0);
		ft_printf("--- c y c l e ---\n");
	}
	return (1);
}
