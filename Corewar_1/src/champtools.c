/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champtools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:55:17 by abinois           #+#    #+#             */
/*   Updated: 2019/08/28 19:01:36 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			mem_stock(t_data *data, char *content, int content_size)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!D->mem_stock)
	{
		if (!(D->mem_stock = ft_alloc_gc(D->mem_size, sizeof(char), D->gc)))
			return (0);
		D->mem_stock_index = 0;
	}
	if (D->mem_stock_index + content_size >= D->mem_size)
	{
		D->mem_size += MEMSIZE;
		tmp = D->mem_stock;
		if (!(D->mem_stock = ft_alloc_gc(D->mem_size, sizeof(char), D->gc)))
			return (0);
		ft_memcpy(D->mem_stock, tmp, D->mem_size - MEMSIZE);
	}
	while (++i < content_size)
		D->mem_stock[D->mem_stock_index++] = content[i];
	return (1);
}

int			change_endian(t_data *data, char *h, int size)
{
	char	endian[size];
	int		i;

	i = -1;
	while (++i < size)
		endian[i] = h[size - 1 - i];
	if (!(mem_stock(D, endian, size)))
		return (0);
	return (1);
}
/*
int			change_endian(t_data *data, unsigned int h)
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
*/

int			fc_namecom(t_data *data, char *namecom, int size)
{
	int		i;

	i = 0;
	go_to_next_elem(D, &D->curr_line, &D->curr_index);
	if (*(D->line) != '"')
		return (get_error(D, syntax, NULL));
	D->line++;
	while (i < size)
	{
		if (!(*D->line))
			if (!(get_new_read(D)))
				return (0);
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
	namecom[i] = '\0';
	D->line++;
	return (0);
}
