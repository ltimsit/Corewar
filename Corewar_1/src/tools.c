/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:16:38 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 17:32:03 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>

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
