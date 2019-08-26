/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/26 19:41:21 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		init_data(t_data *data)
{
	if (!(D->gc = (t_gc *)malloc(sizeof(t_gc))))
		return (0);
	D->gc->list = NULL;
	D->gc->head = NULL;
	D->gc->size = 0;
	D->err = 0;
	D->line = NULL;
	D->start = NULL;
	D->curr_line = 0;
	D->curr_index = 0;
	D->chmp_name = NULL;
	D->chmp_com = NULL;
	D->name_set = false;
	D->comment_set = false;
	D->mem_stock = NULL;
	D->mem_size = MEMSIZE;
	D->header.magic = COREWAR_EXEC_MAGIC;
	D->header.prog_size = 23;
	fill_op_and_err_tab();
	return (1);
}

void	print_error(t_data *data, char *elem)
{
	if (D->err)
	{
		if (!elem)
			ft_printf("%s\n", err_tab[D->err]);
		else
			ft_printf("%s[%d, %d] %s\n", err_tab[D->err], D->curr_line,
					D->curr_index, elem);
	}
}

int		get_fd_file(char *filename)
{
//	(void)filename;
	int fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

void	write_in_file(t_data *data, char *output)
{
	int	fd;

	fd = open("test.cor", O_CREAT | O_RDWR, 0666);
	write(fd, output, D->mem_stock_index);
}

int		main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (0);
	if ((D.fd = get_fd_file(av[1])) == -1)
		return (0);
	if (!(init_data(&D)))
		return (0);
	if (!(read_and_dispatch(&D)))
		return (0);
	else
	{
		ft_printf("{under}{cyan}Writing output file{reset}\n");
		write_in_file(&D, D.mem_stock);
	}
	ft_free_gc(D.gc);
	free(D.gc);
	return (0);
}
