/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/01 10:55:38 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"

void print_arena( t_arena *arena)
{
	unsigned int i;
	unsigned int count;

	i = -1;
	count = 0;
	while (++i < 32)
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
	//	print_process(&arena->champ[i]);
	}

}

int		update_pc(int old_pc, int i)
{
	return ((old_pc + i) % MEM_SIZE);
}


void	check_process(t_arena *arena, t_process *process)
{
	char opcode;

	if (!process->c_todo)
	{
		if ((opcode = arena->field[process->pc]) > 0 && opcode < 17)
		{
			ft_printf("\n");
			read_instruction(arena, process, opcode);
		}
		else
			process->pc = update_pc(process->pc, 1);
		process->c_done++;
	}
	else if (process->c_done < process->c_todo)
	{
		process->c_done++;
	}
	else
	{
		ft_printf("exec\n");
		process->pc = process->pc_next;
		execute_sti(process, arena);
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
	int j;

	j = -1;
	while (++j < 26)
	{
		i = -1;
		while (++i < arena->nb_champ)
		{
//			ft_printf("boucle cycle\n");
			process_champ(arena, &arena->champ[i]);
//			ft_printf("cycle : %d\n", j + 1);
//			print_arena(arena);
//			ft_putchar('\n');
		}
	}
	print_arena(arena);
}
