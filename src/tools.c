/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:16:38 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/10 15:58:38 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>
#include <stdlib.h>

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
	if (D->gc)
	{
		ft_free_gc(D->gc);
		free(D->gc);
	}
	exit(0);
	return (0);
}

void	fill_op_and_err_tab(void)
{
	g_err_tab[0] = "lexical error";
	g_err_tab[1] = "syntax error";
	g_err_tab[2] = "read error !";
	g_err_tab[3] = "param error";
	g_err_tab[4] = "missing coma";
	g_err_tab[5] = "malloc error !";
	g_err_tab[6] = "file error !";
	g_err_tab[7] = "not enough data at EOF !";
}

int		get_new_read(t_data *data)
{
	int		ret;

	ret = 0;
	if (!D->start
			&& !(D->start = ft_alloc_gc(READSIZE + 1, sizeof(char), D->gc)))
		get_error(D, malloc_err, NULL);
	if ((ret = read(D->fd, D->start, READSIZE)) == -1)
		get_error(D, read_error, NULL);
	D->start[ret] = '\0';
	D->line = D->start;
	return (ret ? 1 : 0);
}
