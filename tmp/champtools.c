/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champtools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:55:17 by abinois           #+#    #+#             */
/*   Updated: 2019/08/26 18:16:08 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			mem_stock(t_data *data, char *content, int content_size)
{
	int i;
	char *tmp;

	i = -1;
	if (!data->mem_stock)
	{
		if (!(data->mem_stock = ft_alloc_gc(data->mem_size, sizeof(char), data->gc)))
			return (0);
		data->mem_stock_index = 0;
	}
	if (!data->mem_stock_index + content_size >= data->mem_size)
	{
		data->mem_size += MEMSIZE;
		tmp = data->mem_stock;
		if (!(data->mem_stock = ft_alloc_gc(data->mem_size, sizeof(char), data->gc)))
			return (0);
		ft_memcpy(data->mem_stock, tmp, data->mem_size - MEMSIZE);
	}
	while (++i < content_size)
		data->mem_stock[data->mem_stock_index++] = content[i];
	return (1);
}

int			put_header(t_data *data, unsigned int h)
{
	char	endian[sizeof(h)];
	int		i;

	i = -1;
	while (++i < (int)sizeof(h))
		endian[i] = ((char *)(&h))[sizeof(h) - 1 - i];
	if (!(mem_stock(D, endian, sizeof(h))))
		return (0);
	return (1);
}

int			fill_name(t_data *data, int *i, int *j, char *name)
{
	while (*(++(D->line)) != '"')
	{
		if (*i == PROG_NAME_LENGTH)
			return (get_error(D, syntax));
		if (!*D->line)
		{
			if (!(get_new_read(data)))
				return (0);
			continue ;
		}
		if (*D->line == '\n')
			*j++;
		name[*i++] = *D->line;
	}
	D->line++;
	*i++;
	return (1);
}

int			fill_comment(t_data *data, int *i, int *j, char *comment)
{
	while (*(++(D->line)) != '"')
	{
		if (*i == COMMENT_LENGTH)
			return (get_error(D, syntax));
		if (!*D->line)
		{
			if (!(get_new_read(data)))
				return (0);
			continue ;
		}
		if (*D->line == '\n')
			*j++;
		comment[*i++] = *D->line;
	}
	D->line++;
	*i++;
	return (1);
}

int			fc_name(t_data *data, int type, int j)
{
	int		i;
	int		j;
	char	name[PROG_NAME_LENGTH];

	(void)type;
	get_to_next_elem(D, &(D->curr_line), &(D->curr_index))
	i = 0;
	j = 0;
	if (D->line != '"')
		return (get_error(D, syntax));
	if (!fill_name(D, &i, &j, name))
		return (0);
	D->curr_index += i;
	D->curr_line += j;
	while (i < PROG_NAME_LENGTH)
		name[i++] = '\0';
	if (!(put_header(D, COREWAR_EXEC_MAGIC))
			|| !(mem_stock(D, name, PROG_NAME_LENGTH)))
		return (0);
	D->name_set = true;
	return (1);
}

int			fc_comment(t_data *data, int type, int j)
{
	int		i;
	char	comment[COMMENT_LENGTH];

	(void)type;
	j = skip_sp(D->line, j + 1);
	D->curr_index = j;
	i = 0;
	if (D->line[j] != '"')
		return (get_error(D, syntax));
	while (D->line[++j] != '"')
		if (!D->line[j] || i == COMMENT_LENGTH)
			return (get_error(D, syntax));
		else
			comment[i++] = D->line[j];
	while (i < COMMENT_LENGTH)
		comment[i++] = '\0';
	if (!(put_header(D, 23)) || !(mem_stock(D, comment, COMMENT_LENGTH)))
		return (0);
	D->comment_set = true;
	return (1);
}

char		*stock_namecom(char *line)
{
	int		start;
	int		end;
	char	*namecom;
	
	ft_printf("line=%s\n", line);
	start = ft_skip_nochar(line, '"', 0);
	end = ft_skip_nochar(line + start + 1, '"', 0);
	namecom = ft_strsub((const char **)&line, start + 1, end, 0);
	return (namecom);
}
