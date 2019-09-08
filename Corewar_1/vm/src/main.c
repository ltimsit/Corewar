/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/08 18:42:07 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include <unistd.h>
#include <stdlib.h>

unsigned char	*open_read(char *filename, unsigned char *buffer)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Open failed\n");
	ret = read(fd, buffer, CHAMP_MAX_SIZE + sizeof(header_t));
	return (buffer);
}

unsigned int	change_endian(unsigned int little)
{
	unsigned char	t_little[4];
	unsigned char	t_big[4];
	unsigned int	big;
	int				i;

	i = -1;
	ft_memcpy(t_little, &little, sizeof(unsigned int));
	while (++i < 4)
		t_big[i] = t_little[3 - i];
	ft_memcpy(&big, t_big, sizeof(unsigned int));
	return (big);
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

void			print_usage(t_arena *arena)
{
	ft_printf("Usage: ./corewar [-n N <champion1.cor>] [-dis -dump N]\n");
	ft_printf("\t-dis\t\t\t: Mlx output mode\n");
	ft_printf("\t-dump N\t\t\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t-n N <champion.cor>\t: Sets champion id to N \n");
	ft_free_gc(arena->gc);
	free(arena->gc);
	exit(0);
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
			arena->display_on = 1;
		else if (!ft_strcmp(av[i], "-dump"))
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
//	int		i;
	t_arena	arena;

	ft_bzero(&arena, sizeof(t_arena));
	if (!(arena.gc = (t_gc*)malloc(sizeof(t_gc))))
		ft_error("Malloc error\n");
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
/* 
	i = -1;
	while (++i < arena.nb_champ)
		print_champ(arena.champ+ i);
	return (0);
	*/
	if (arena.display_on)
		init_display(&arena);
	else
		while (1)
			launch_fight(&arena);
	return (0);
}
