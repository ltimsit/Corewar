/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/10 16:41:04 by abinois          ###   ########.fr       */
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
		ft_error(arena, "Open failed\n");
	ret = read(fd, buf, CHAMP_MAX_SIZE + sizeof(header_t));
	return (buf);
}

void			sort_champ(t_arena *arena)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	while (++i < arena->nb_champ - 1)
	{
		j = i;
		while (++j < arena->nb_champ)
			if (arena->champ[i].id < arena->champ[j].id)
			{
				tmp = arena->champ[i].id;
				arena->champ[i].id = arena->champ[j].id;
				arena->champ[j].id = tmp;
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
			arena->display_on = 1;
			arena->dump_cycle = 0;
		}
		else if (!ft_strcmp(av[i], "-dump") && !arena->display_on)
		{
			if (++i < ac)
				arena->dump_cycle = ft_atoi(av[i]);
			else
				print_usage(arena);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			if (++i < ac)
				id_champ = ft_atoi(av[i]);
			else
				print_usage(arena);
		}
		else if (av[i][0] != '-')
			create_add_champ(av[i], arena, id_champ++);
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

	ft_bzero(&arena, sizeof(t_arena));
	if (!(arena.gc = (t_gc*)malloc(sizeof(t_gc))))
		ft_error(&arena, "Malloc error\n");
	ft_bzero(arena.gc, sizeof(t_gc));
	arena.cycle_to_die = CYCLE_TO_DIE;
	init_fct_instr_tab();
	init_fct_exec_tab();
	set_op_table(&arena);
	check_argv(&arena, av, ac);
	if (!arena.nb_champ)
		print_usage(&arena);
	sort_champ(&arena);
	load_champ(&arena);
	if (arena.display_on)
		init_display(&arena);
	else
		while (1)
			launch_fight(&arena);
	return (0);
}
