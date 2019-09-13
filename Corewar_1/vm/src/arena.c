/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/13 11:56:00 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

void	print_arena(t_arena *arena)
{
	int i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < A->nb_champ)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i + 1, A->champ[i].h.prog_size,
		A->champ[i].h.prog_name, A->champ[i].h.comment);
	}
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % 32) && i != MEM_SIZE - 1)
			ft_printf("{grey}%s%-.4p : {reset}", !i ? "" : "\n", i);
		ft_printf("%.2x", A->field[i]);
		if (i % 32 != 31)
			ft_putchar(' ');
	}
}

void	fill_color_value(unsigned char *carriage, int size, int p_nb)
{
	int i;

	i = -1;
	while (++i < size)
		carriage[i] += (1 << p_nb);
}

void	execution(t_arena *arena, t_process *process)
{
	read_instr(A, process, process->opcode);
	if (!process->param.error)
		g_fct_exec[(int)process->opcode](process, A);
	A->carriage[process->pc] -= 16;
	process->pc = (process->pc + process->pc_next) % MEM_SIZE;
	A->carriage[process->pc] |= 1 << 4;
	process->c_done = 0;
	process->c_todo = 0;
}

void	check_process(t_arena *arena, t_process *process)
{
	char	opcode;

	A->carriage[process->pc] |= 1 << 4;
	if (!process->c_todo)
	{
		if ((opcode = A->field[process->pc]) > 0 && opcode < 17)
		{
			process->opcode = opcode;
			process->c_todo = A->op[(int)opcode - 1].time - 1;
			process->c_done++;
		}
		else
		{
			A->carriage[process->pc] ^= 1 << 4;
			process->pc = update_pc(process->pc, 1);
			A->carriage[process->pc] |= 1 << 4;
		}
	}
	else if (process->c_done < process->c_todo)
		process->c_done++;
	else
		execution(A, process);
}

void	launch_fight(t_arena *arena)
{
	if (A->total_cycle == A->dump_cycle)
		exit_dump(A);
	if (++(A->curr_cycle) < A->cycle_to_die)
	{
		A->total_cycle++;
		process_process(A);
		if (A->dis && (++(A->dis->cpt_to_speed) == A->dis->speed))
			print_map(A, A->curr_cycle);
	}
	else
	{
		A->nb_live = verif_process(A, A->p_head);
		if (!A->p_head)
			print_winner(A);
		if ((A->nb_live >= NBR_LIVE) || (++A->nb_check >= MAX_CHECKS))
		{
			A->cycle_to_die -= CYCLE_DELTA;
			A->nb_check = 0;
		}
		A->curr_cycle = -1;
	}
	if (A->total_cycle == A->dump_cycle)
		exit_dump(A);
}
