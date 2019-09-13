/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/13 16:44:18 by avanhers         ###   ########.fr       */
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
	ret = read(fd, buf, CHAMP_MAX_SIZE + sizeof(t_header));
	return (buf);
}

void			print_winner(t_arena *arena)
{
	char	*winner;

	if (!(winner = check_valid_champ(A->last_living_champ, A)))
	{
		ft_printf("☠️  Personne n'est en vie ! ☠️ \n");
		ft_free_gc(A->gc);
		ft_memdel((void**)&(A->gc), 0);
		exit(1);
	}
	else
	{
		ft_printf("😎  Le joueur %s a gagné ! 😎 \n", winner);
		ft_free_gc(A->gc);
		ft_memdel((void**)&(A->gc), 0);
		exit(1);
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
			if (++i < ac)
				A->cycle_before_dis = ft_atoi(av[i]);
			if (i == ac || A->cycle_before_dis < 0 || !ft_isdigit(av[i][0]))
				print_usage(A);
			else
				A->display_on = 1;
		}
		else if (!ft_strcmp(av[i], "-dump"))
		{
			if (++i < ac)
				A->dump_cycle = ft_atoi(av[i]);
			if (i == ac || A->dump_cycle < 0 || !ft_isdigit(av[i][0]))
				print_usage(A);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			if (++i < ac)
				id_champ = ft_atoi(av[i]);
			else
				print_usage(A);
		}
		else
			create_add_champ(av[i], A, id_champ++);
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
	A.dump_cycle = -1;
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
	else
		while (1)
			launch_fight(&A);
	return (0);
}
