/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 16:54:36 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include <unistd.h>
#include <stdlib.h>

unsigned char	*open_read(t_arena *arena, char *filename, unsigned char *buf)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error(A, "Open failed\n");
	ret = read(fd, buf, CHAMP_MAX_SIZE + sizeof(t_header));
	return (buf);
}

void			sort_champ(t_arena *arena)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	while (++i < A->nb_champ - 1)
	{
		j = i;
		while (++j < A->nb_champ)
			if (A->champ[i].id < A->champ[j].id)
			{
				tmp = A->champ[i].id;
				A->champ[i].id = A->champ[j].id;
				A->champ[j].id = tmp;
			}
	}
}

int				check_argv(t_arena *arena, char **av, int ac)
{
	int		i;
	int		id_champ;

	i = 0;
	id_champ = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-dis"))
		{
			A->display_on = 1;
			A->dump_cycle = 0;
		}
		else if (!ft_strcmp(av[i], "-dump") && !A->display_on)
		{
			if (++i < ac)
				A->dump_cycle = ft_atoi(av[i]);
			else
				print_usage(A);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			if (++i < ac)
				id_champ = ft_atoi(av[i]);
			else
				print_usage(A);
		}
		else if (av[i][0] != '-')
			create_add_champ(av[i], A, id_champ++);
		else
		{
			ft_printf("{red}unknown option \"%s\"\n{reset}", av[i]);
			exit(0);
		}
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_arena	arena;

	ft_bzero(&A, sizeof(t_arena));
	if (!(A.gc = (t_gc*)malloc(sizeof(t_gc))))
		ft_error(&A, "Malloc error\n");
	ft_bzero(A.gc, sizeof(t_gc));
	A.cycle_to_die = CYCLE_TO_DIE;
	init_fct_instr_tab();
	init_fct_exec_tab();
	set_op_table(&A);
	check_argv(&A, av, ac);
	if (!A.nb_champ)
		print_usage(&A);
	sort_champ(&A);
	load_champ(&A);
	arena.curr_cycle = -1;
	if (A.display_on)
		init_display(&A);
	else
		while (1)
			launch_fight(&A);
	return (0);
}
