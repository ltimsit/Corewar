/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/31 17:31:36 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"

void print_arena( t_arena *arena)
{
	unsigned int i;
	unsigned int count;

	i = -1;
	count = 0;
	while (++i < MEM_SIZE)
	{
		btohex(arena->field[i]);
		count++;
		if (count == 32)
		{
			ft_putchar('\n');
			count = 0;
		}
		else
			ft_putchar(' ');
	}
}

void	load_champ(t_arena *arena)
{
	int	i;
	int	space;

	i = -1;
	space = MEM_SIZE / arena->nb_champ;
	while (++i < arena->nb_champ)
	{
		ft_memcpy(arena->field + (i * space), arena->champ[i].buff,
		   	arena->champ[i].h.prog_size);
		arena->champ[i].process->pc = i * space;
		print_process(&arena->champ[i]);
	//	arena->champ[i];
	}
}

int		update_pc(int old_pc, int i)
{
	return ((old_pc + i) % MEM_SIZE);
}



void	check_process(t_arena *arena, t_process *process)
{
	if (!process->c_todo)
	{
		if (arena->field[process->pc] > 0 && arena->field[process->pc] < 17)
			read_instruction(arena);
		else
			process->pc = update_pc(process->pc, 1);
	}
	else if (process->c_done < process->c_todo)
	{
		process->c_done++;
	}
	else
	{
		process->pc = process->pc_next;
		execute_instruction();
	}
}

void	process_champ(t_arena *arena, t_champ *champ)
{
	t_process *tmp;

	tmp = champ->p_head;
	while (tmp)
	{
		check_process(arena, tmp);
		tmp = tmp->next;
	}
}

void launch_fight(t_arena *arena)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < arena->nb_champ)
			process_champ(arena, &arena->champ[i]);
	}
}
