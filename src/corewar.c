/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 12:49:03 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		init_data(t_data *data)
{
	ft_bzero(D, sizeof(t_data));
	if (!(D->gc = (t_gc *)malloc(sizeof(t_gc))))
		get_error(D, malloc_err, NULL);
	ft_bzero(D->gc, sizeof(t_gc));
	if (!(D->label = (t_label *)ft_alloc_gc(1, sizeof(t_label), D->gc)))
		get_error(D, malloc_err, NULL);
	ft_bzero(D->label, sizeof(t_label));
	D->curr_line = 1;
	D->curr_index = 1;
	D->mem_stock_index = sizeof(D->header);
	D->mem_size = MEMSIZE;
	D->header.magic = COREWAR_EXEC_MAGIC;
	fill_op_and_err_tab();
	return (1);
}

void	print_error(t_data *data, char *elem)
{
	if (D->err)
	{
		if (D->err == 8)
			ft_printf("{red}%s{reset} : [%.3d:%.3d]\n", g_err_tab[D->err],
					D->curr_line, D->curr_index);
		else if (!elem)
			ft_printf("{red}%s\n{reset}", g_err_tab[D->err]);
		else
			ft_printf("{red}%s{reset} : [%.3d:%.3d] -> \"%s\"\n",
					g_err_tab[D->err], D->curr_line, D->curr_index,	elem);
	}
}

int		get_fd_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("{red}Read error or File \"%s\" does not exist\n{reset}",
				filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	write_in_file(t_data *data, char *output, char *filename)
{
	int		fd;
	char	file[128];
	char	*ext;
	int		i;

	ext = ".cor";
	i = -1;
	while (i < 128 - 4 && filename[++i] && filename[i] != '.')
		file[i] = filename[i];
	file[i] = '\0';
	if (i == 128 - 4 || !filename[i])
		get_error(D, file_err, NULL);
	ft_strcat(file, ext);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_printf("{cyan}Writing output program to \"%s\"{reset}\n", file);
	write(fd, output, D->size_mem_tot);
}

int		main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (print_usage());
	init_data(&D);
	D.fd = get_fd_file(av[1]);
	if (!(get_header(&D)))
		return (0);
	else
		write_in_file(&D, D.mem_stock, av[1]);
	ft_free_gc(D.gc);
	free(D.gc);
	return (0);
}
