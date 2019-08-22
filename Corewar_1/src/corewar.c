/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/21 17:50:59 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include "ft_printf.h"

int		init_data(t_data *data)
{
	data->curr_line = -1;
	data->gc = NULL;
	data->err = 0;
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
	int fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

int		main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if (!(data.fd = get_fd_file(av[1])))
		return (0);
	init_data(&data);
	if (!manage_lines(&data))
		print_error(&data);
}
