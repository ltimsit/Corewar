/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/03 15:55:54 by ltimsit-         ###   ########.fr       */
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

void	check_process(t_arena *arena, t_process *process)
{
	char opcode;
	int j;

//	ft_printf("{red}todo = %d\n{reset}", process->c_todo);
	if (!process->c_todo)
	{
		if ((opcode = arena->field[process->pc]) > 0 && opcode < 17)
		{
	//		ft_printf("process opcode == %hhd\n", opcode);
			process->opcode = opcode;
			read_instruction(arena, process, opcode);
		}
		else
			process->pc = update_pc(process->pc, 1);
		process->c_done++;
	}
	else if (process->c_done < process->c_todo)
	{
//		ft_printf("cycle -- \n");
		process->c_done++;
	}
	else
	{
//		ft_printf("exec\n");
		n_print_pc(process->pc, arena, 1);
		process->pc = update_pc(process->pc, process->pc_next);
//		ft_printf("{yellow}pc = %d\n{reset}", process->pc);
		process->c_done = 0;
		process->c_todo = 0;
		g_fct_exec[(int)process->opcode](process, arena);
	}
	j = -1;
	while (++j < 17)
	{
		n_print_reg(process, arena, j);
	}
	n_print_pc(process->pc, arena, 0);
}

void	process_champ(t_arena *arena, t_champ *champ)
{
	t_process *tmp;

	tmp = champ->p_head;
	while (tmp)
	{
		check_process(arena, tmp);
		tmp = tmp->next;
//		ft_printf("tmp = %p\n", tmp);
	}
}

void launch_fight(t_arena *arena)
{
	int i;
	int j;

	j = -1;
//	print_arena(arena);
//	ft_putchar('\n');
	init_ncurses(arena);
	nprint_arena(arena);
	while (getch())//++j < 44)
	{
		i = -1;
		while (++i < arena->nb_champ)
		{
	//		ft_printf("boucle cycle : %d\n", j + 1);
			process_champ(arena, &arena->champ[i]);
//			ft_printf("cycle : %d\n", j + 1);
	//		print_arena(arena);
//			ft_putchar('\n');
		}
	}
//	print_arena(arena);
}
