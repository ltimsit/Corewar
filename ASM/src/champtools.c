/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champtools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:55:17 by abinois           #+#    #+#             */
/*   Updated: 2019/09/18 18:30:14 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>

int			get_new_read(t_data *data)
{
	if (!D->start
			&& !(D->start = ft_alloc_gc(READSIZE + 1, sizeof(char), D->gc)))
		get_error(D, malloc_err, NULL);
	if (D->read_ret && (D->line - D->start) != D->read_ret)
		get_error(D, backzer, NULL);
	if ((D->read_ret = read(D->fd, D->start, READSIZE)) == -1)
		get_error(D, read_error, NULL);
	D->start[D->read_ret] = '\0';
	D->line = D->start;
	return (D->read_ret ? 1 : 0);
}

int			mem_stock(t_data *data, char *content, int content_size)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!D->mem_stock)
		if (!(D->mem_stock = ft_alloc_gc(D->mem_size, sizeof(char), D->gc)))
			get_error(D, malloc_err, NULL);
	if (D->mem_stock_index + content_size >= D->mem_size)
	{
		D->mem_size += MEMSIZE;
		tmp = D->mem_stock;
		if (!(D->mem_stock = ft_alloc_gc(D->mem_size, sizeof(char), D->gc)))
			get_error(D, malloc_err, NULL);
		ft_memcpy(D->mem_stock, tmp, D->mem_size - MEMSIZE);
	}
	while (++i < content_size)
		D->mem_stock[D->mem_stock_index++] = content[i];
	return (1);
}

void		fc_namecom(t_data *data, char *namecom, int size, int i)
{
	go_to_next_elem(D, &D->curr_line, &D->curr_index, 0);
	if (*(D->line) != '"')
		get_error(D, dquote, NULL);
	D->line++;
	while (i < size)
	{
		if (!*D->line && !get_new_read(D))
			get_error(D, data_err, NULL);
		if (*D->line != '"')
		{
			if (*(D->line) == '\n')
			{
				D->curr_line++;
				D->curr_index = 0;
			}
			namecom[i++] = *(D->line)++;
			D->curr_index++;
		}
		else
			namecom[i++] = '\0';
	}
	if (*(D->line) != '"')
		get_error(D, dquote, NULL);
	namecom[i] = '\0';
	D->line++;
}
