/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:21:53 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/26 18:16:04 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.c"
#include <unistd.h>

int	set_header(t_data *data)
{
	if (!(put_header(data, D->header.magic))
			|| !(mem_stock(D, D->header.prog_name, PROG_NAME_LENGTH))
			|| !(put_header(data, D->header.prog_size))
			|| !(mem_stock(D, D->header.comment, COMMENT_LENGTH)))
		return (0);
}

int get_new_read(t_data *data)
{
	if (!(D->line = ft_alloc_gc(SIZE_READ + 1, sizeof(char), D->gc)))
		return (0);
	if (!(read(D->fd, D->live, SIZE_READ)))
		return (0);
	D->line[SIZE_READ] = '\0';
	return (1);
}

int	get_name(t_data *data)
{
	get_to_next_elem(data, D->curr_line, D->curr_index);
	
}

int get_header(t_data *data)
{
	char cmd[14];
	int i;

	while (!(D->name_set && D->comment_set))
	{
		get_to_next_elem(data, &(D->curr_line), &(D->curr_index));
		i = get_elem(data, cmd, 14);
		if (!ft_strcmp(cmd, NAME_CMD_STRNG) && !D->name_set)
		{
			D->line += i;
			D->curr_index += i;
			fc_name(data);
		}
		if (!ft_strcmp(cmd, COMMENT_CMD_STRING) && !D->comment_set)
		{
			D->line += i;
			D->curr_index += i;
			fc_comment(data);
		}
	}
	return (1);
}

int get_elem (t_data *data, char *tab, int tab_size)
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

int	get_to_next_elem(t_data *data, int *line_id, int *col_id)
{
	int i;
	int index;

	while ((i = skip_space(D->line, 0)))
	{
		line += i;
		if (*D->line == '\n')
		{
			*col_id++;
			*line_id = 0;
			continue ;
		}
		else if (!*D->line)
			get_new_read(D);
		else
		{
			*line_id += i;
			return (1);
		}
	}
	return (0);
}
