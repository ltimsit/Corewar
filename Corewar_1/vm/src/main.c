/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:19:09 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/05 14:55:23 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include <unistd.h>
#include <stdlib.h>

unsigned char		*open_read(char *filename, unsigned char *buffer)
{	
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);	
	if (fd == -1)
		ft_error("Open failed\n");
	ret = read(fd, buffer, CHAMP_MAX_SIZE + sizeof(header_t));
	return (buffer);
}

unsigned int		change_endian(unsigned int little)
{
	unsigned char 	t_little[4];
	unsigned char 	t_big[4];
	unsigned int 	big;
	int				i;

	i = -1;
	ft_memcpy(t_little, &little, sizeof(unsigned int));
	while (++i < 4)
		t_big[i]= t_little[3 -i];
	ft_memcpy(&big, t_big, sizeof(unsigned int));
	return (big);
}

void				sort_champ(t_arena *arena)
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

int					main(int ac, char **av)
{
	int 	i;
	t_arena arena;
	i = 0;
	ft_bzero(&arena,sizeof(t_arena));
	if (!(arena.gc = (t_gc*)malloc(sizeof(t_gc))))
		ft_error("Malloc error\n");
	ft_bzero(arena.gc, sizeof(t_gc));
	arena.cycle_to_die = CYCLE_TO_DIE;
	init_fct_instr_tab();
	init_fct_exec_tab();
	set_op_table(&arena);
	if (!ft_strcmp(av[1], "-dis"))
	{
		arena.display_on = 1;
		i++;
	}
	while (i + 1 < ac)
		create_add_champ(av[i++ + 1], &arena);
	i = -1;
	sort_champ(&arena);
	load_champ(&arena);
//	launch_fight(&arena);
	if (arena.display_on)	
		init_display(&arena);
	else
	{
		while (1)
			launch_fight(&arena);
	}
	return (0);
}
