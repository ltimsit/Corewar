/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/23 13:09:46 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include "ft_printf.h"

int		init_data(t_data *data)
{
	data->curr_line = -1;
	data->gc = NULL;
	data->head_gc = NULL;
	data->err = 0;
	data->name_set = false;
	data->comment_set = false;
	fill_op_and_err_tab();
	return (1);
}

void	print_error(t_data *data)
{
	if (data->err)
		ft_printf("%s[%d, %d] %s\n", err_tab[data->err], data->curr_line,
				data->curr_index, data->line);
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
	if ((data.fd = get_fd_file(av[1])) == -1)
		return (0);
	init_data(&data);
	if (!manage_lines(&data))
		print_error(&data);
}
