/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/24 13:26:29 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

int		init_data(t_data *data)
{
	D->gc = NULL;
	D->head_gc = NULL;
	D->err = 0;
	D->line = NULL;
	D->curr_line = -1;
	D->chmp_name = NULL;
	D->chmp_com = NULL;
	D->name_set = false;
	D->comment_set = false;
	fill_op_and_err_tab();
	return (1);
}

void	print_error(t_data *data)
{
	if (D->err)
		ft_printf("%s[%d, %d] %s\n", err_tab[D->err], D->curr_line,
				D->curr_index, D->line);
}

int		get_fd_file(char *filename)
{
	return (open(filename, O_RDONLY));
}

int		main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if ((D.fd = get_fd_file(av[1])) == -1)
		return (0);
	init_data(&D);
	if (!manage_lines(&D))
		print_error(&D);
}
