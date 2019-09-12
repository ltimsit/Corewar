/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 12:10:33 by abinois          ###   ########.fr       */
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
			ft_printf("%s%-.4p : ", !i ? "" : "\n", i);
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

void	load_champ(t_arena *arena)
{
	int		i;
	int		space;

	i = -1;
	space = MEM_SIZE / A->nb_champ;
	while (++i < A->nb_champ)
	{
		ft_memcpy(A->field + (i * space), A->champ[i].buff,
				A->champ[i].h.prog_size);
		fill_color_value(A->carriage + (i * space),
				A->champ[i].h.prog_size, i);
		add_process(A, A->champ[i].id, i);
		A->process->pc = i * space;
	}
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
			process->c_todo = A->op[(int)opcode - 1].time;
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
	{
		read_instr(A, process, process->opcode);
		if (!process->param.error)
			g_fct_exec[(int)process->opcode](process, A);
		A->carriage[process->pc] -= 16;
		process->pc = update_pc(process->pc, process->pc_next);
		process->c_done = 0;
		process->c_todo = 0;
		check_process(A, process);
	}
}

void	process_process(t_arena *arena)
{
	t_process *tmp;

	tmp = A->p_head;
	while (tmp)
	{
		check_process(A, tmp);
		tmp = tmp->next;
	}
}

int		verif_process(t_arena *arena, t_process *head)
{
	t_process	*tmp;
	int			nb_live;
	t_process	*prev;

	prev = NULL;
	tmp = head;
	nb_live = 0;
	while (tmp)
	{
		if (!tmp->nb_live)
			del_process(A, tmp, prev);
		else
		{
			nb_live += tmp->nb_live;
			tmp->nb_live = 0;
			prev = tmp;
		}
		tmp = tmp->next;
	}
	return (nb_live);
}

void	print_winner(t_arena *arena)
{
	char	*winner;

	if (!(winner = check_valid_champ(A->last_living_champ, A)))
	{
		ft_printf("☠️  Personne n'est en vie ! ☠️ \n");
		ft_free_gc(A->gc);
		free(A->gc);
		exit(1);
	}
	else
	{
		ft_printf("😎  Le joueur %s a gagné ! 😎 \n", winner);
		ft_free_gc(A->gc);
		free(A->gc);
		exit(1);
	}
}

void	launch_fight(t_arena *arena)
{
	static int j = -1;

	if (++j < A->cycle_to_die)
	{
		A->total_cycle++;
		process_process(A);
		if (A->dis)
			print_map(A, j);
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
		j = -1;
	}
	if (A->dump_cycle && A->total_cycle == A->dump_cycle)
		exit_dump(A);
}
