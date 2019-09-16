/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/16 11:16:18 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include <unistd.h>
#include <stdlib.h>

unsigned char	*open_read(t_arena *arena, char *file, unsigned char *buf)
{
	int	fd;
	int	ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(A, "Open failed\n");
	if ((ret = read(fd, buf, CHAMP_MAX_SIZE + sizeof(t_header))) == -1)
		ft_error(A, "Read failed\n");
	if ((ret = close(fd)) == -1)
		ft_error(A, "Close failed\n");
	return (buf);
}

int				get_arg(int i, char **av, int ac, int *argument)
{
	if (i < ac)
		*argument = ft_atoi(av[i]);
	if (i == ac
		|| (ft_strcmp(av[i - 1], "-n") && *argument < 0)
		|| !ft_str_is_digit(av[i]))
		return (0);
	return (1);
}

void			check_argv(t_arena *arena, char **av, int ac)
{
	int		i;
	int		id_champ;

	i = 0;
	id_champ = 1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-dis"))
		{
			if (!(get_arg(++i, av, ac, &A->cycle_before_dis)))
				print_usage(A);
			A->display_on = 1;
		}
		else if (!ft_strcmp(av[i], "-dump")
			&& !get_arg(++i, av, ac, &A->dump_cycle))
			print_usage(A);
		else if (!ft_strcmp(av[i], "-n")
			&& !get_arg(++i, av, ac, &id_champ))
			print_usage(A);
		else if (++(A->nb_champ) <= MAX_PLAYERS)
			create_add_champ(av[i], A, id_champ++);
	}
}

void			init_corewar(t_arena *arena)
{
	ft_bzero(A, sizeof(t_arena));
	if (!(A->gc = (t_gc*)malloc(sizeof(t_gc))))
		ft_error(A, "Malloc error\n");
	ft_bzero(A->gc, sizeof(t_gc));
	A->cycle_to_die = CYCLE_TO_DIE;
	A->dump_cycle = -1;
	init_fct_instr_tab();
	init_fct_exec_tab();
	set_op_table(A);
}

int				main(int ac, char **av)
{
	t_arena	arena;

	init_corewar(&A);
	check_argv(&A, av, ac);
	if (!A.nb_champ)
		print_usage(&A);
	sort_champ(&A);
	load_champ(&A);
	if (A.display_on)
	{
		while (A.total_cycle != A.cycle_before_dis)
			launch_fight(&A);
		init_display(&A);
	}
	while (1)
		launch_fight(&A);
	return (0);
}
