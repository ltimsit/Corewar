/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/29 18:55:46 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		init_data(t_data *data)
{
	if (!(D->gc = (t_gc *)malloc(sizeof(t_gc))))
		get_error(D, malloc_err, NULL);
	D->gc->list = NULL;
	D->gc->head = NULL;
	D->gc->size = 0;
	if (!(D->label = (t_label *)ft_alloc_gc(1, sizeof(t_label), D->gc)))
		get_error(D, malloc_err, NULL);
	D->label->lst_add = NULL;
	D->label->lst_instr = NULL;
	D->label->head_add = NULL;
	D->label->head_instr = NULL;
	D->pc = 0;
	D->err = 0;
	D->line = NULL;
	D->start = NULL;
	D->curr_line = 1;
	D->curr_index = 1;
	D->chmp_name = NULL;
	D->chmp_com = NULL;
	D->name_set = false;
	D->comment_set = false;
	D->mem_stock = NULL;
	D->mem_stock_index = sizeof(D->header);
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
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("read error or file \"%s\" does not exist\n", filename);
		exit(0);
	}
	return (fd);
}

void	write_in_file(t_data *data, char *output, char *filename)
{
	int	fd;
	char file[128];
	char *ext;
	int i;

	ext = ".cora";
	i = -1;
	while (i < 128 - 4 && filename[++i] && filename[i] != '.')
		file[i] = filename[i];
	file[i] = '\0';
	if (i == 128 - 4 || !filename[i])
		get_error(D, file_err, NULL);
	ft_strcat(file, ext);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_printf("{under}{cyan}Writing output file in \"%s\"{reset}\n", file);
	write(fd, output, D->size_mem_tot);
}

int		main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (0);
	if ((D.fd = get_fd_file(av[1])) == -1)
		return (0);
	ft_printf("fdhfdjfd\n");
	if (!(init_data(&D)))
		return (0);
	ft_printf("fdhfdjfd\n");
	if (!(get_header(&D)))
		return (0);
	else
	{
		write_in_file(&D, D.mem_stock, av[1]);
	}
	ft_free_gc(D.gc);
	free(D.gc);
	return (0);
}
