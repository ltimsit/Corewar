/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/19 19:07:29 by ltimsit-         ###   ########.fr       */
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
		if (!(i % 64) && i != MEM_SIZE - 1)
			ft_printf("%s%-.4p : ", !i ? "" : "\n", i);
		ft_printf("%.2x", A->field[i]);
//		if (i % 32 != 31)
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	manage_pc_carriage(t_arena *arena, t_process *process, int new_pc)
{
	if (!(A->carriage[PRO->pc] >> 5 & 1))
		A->carriage[PRO->pc] ^= 1 << 4;
	PRO->pc = update_pc(PRO->pc, new_pc);
	A->carriage[PRO->pc] |= 1 << 4;
	A->carriage[PRO->pc] |= 1 << 5;
}

void	execution(t_arena *arena, t_process *process)
{
	g_fct_instr[(int)(PRO->opcode)](A->op[(int)(PRO->opcode) - 1], PRO, A);
	if (!PRO->param.error)
		g_fct_exec[(int)PRO->opcode](PRO, A);
	manage_pc_carriage(arena, PRO, PRO->pc_next);
	PRO->c_done = 0;
	PRO->c_todo = 0;
}

void	check_process(t_arena *arena, t_process *process)
{
	char	opcode;

	A->carriage[PRO->pc] |= 1 << 4;
	if (!PRO->c_todo)
	{
		if ((opcode = A->field[PRO->pc]) > 0 && opcode < 17)
		{
			PRO->opcode = opcode;
			PRO->c_todo = A->op[(int)opcode - 1].time - 1;
			PRO->c_done++;
			A->carriage[PRO->pc] |= 1 << 5;
		}
		else
			manage_pc_carriage(A, PRO, 1);
	}
	else if (PRO->c_done < PRO->c_todo)
		PRO->c_done++;
	else
		execution(A, PRO);
}

void	launch_fight(t_arena *arena)
{
	if (!A->display_on && A->total_cycle == A->dump_cycle)
		exit_dump(A);
	if (A->curr_cycle < A->cycle_to_die)
	{
		A->total_cycle++;
		A->curr_cycle++;
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
			A->cycle_to_die = A->cycle_to_die < 0 ? 0 : A->cycle_to_die;
			A->nb_check = 0;
		}
		A->curr_cycle = 0;
	}
}
