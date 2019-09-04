/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/04 17:38:05 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

void print_arena( t_arena *arena)
{
	unsigned int i;
	unsigned int count;

	i = -1;
	count = 0;
	while (++i < 77)
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

void    load_champ(t_arena *arena)
{
    int i;
    int space;
    i = -1;
    space = MEM_SIZE / arena->nb_champ;
    while (++i < arena->nb_champ)
    {
        ft_memcpy(arena->field + (i * space), arena->champ[i].buff,
                arena->champ[i].h.prog_size);
        add_process(arena, arena->champ[i].id);
        arena->process->pc = i * space;
    }
}

void	check_process(t_arena *arena, t_process *process)
{
	char opcode;
	int j;

	ft_printf("{blue}process = %p{reset}\n", process);
	ft_printf("{green}head = %p\n{reset}", arena->p_head);
	if (!process->c_todo)
	{
		ft_printf("{cyan}process opcode == %hhd\n{reset}", arena->field[process->pc]);
		if ((opcode = arena->field[process->pc]) > 0 && opcode < 17)
		{
			process->opcode = opcode;
	//		read_instruction(arena, process, opcode);
		}
		else
			process->pc = update_pc(process->pc, 1);
		process->c_done++;
	}
	else if (process->c_done < process->c_todo)
		process->c_done++;
	else
	{
		ft_printf("exec ------ r[0] = %d\n", process->reg[0]);
		read_instruction(arena, process, opcode);
		if (!process->param.error)
		{
			g_fct_exec[(int)process->opcode](process, arena);
		}
		ft_printf("exec ------ r[0] = %d\n", process->reg[0]);
		n_print_pc(process->pc, arena, 1);
		process->pc = update_pc(process->pc, process->pc_next);
		process->c_done = 0;
		process->c_todo = 0;
	}
	j = -1;
	while (++j < 17)
		n_print_reg(process, arena, j);
	n_print_pc(process->pc, arena, 0);
	ft_putendl("- - - END OF CHECK PROCESS - - -");
	ft_printf("{yellow}done = %d\n{reset}", process->c_done);
	ft_printf("{red}todo = %d\n{reset}", process->c_todo);
	ft_printf("{italic}pc next  = %d{reset}\n", process->pc_next);
}

void    process_champ(t_arena *arena)
{
    t_process *tmp;

    tmp = arena->p_head;
    while (tmp)
    {
        check_process(arena, tmp);
        tmp = tmp->next;
    }
}

int     verif_process(t_arena *arena, t_process *head)
{
    t_process   *tmp;
    int         nb_live;
    t_process   *prev;
    prev = NULL;
    tmp = head;
    nb_live = 0;
    while (tmp)
    {
        if (!tmp->nb_live)
            del_process(arena, tmp, prev);
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
	int		i;

	i = -1;
	if (!arena->last_living_champ)
	{
		ft_printf("☠️  Personne n'est en vie ! ☠️ \n");
		ft_free_gc(arena->gc);
		free(arena->gc);
		exit(1);
	}
	while (++i < arena->nb_champ)
		if (arena->last_living_champ == arena->champ[i].id)
		{
			ft_printf("😎  Le joueur %s a gagné ! 😎 \n",
					arena->champ[i].h.prog_name);
			ft_free_gc(arena->gc);
			free(arena->gc);
			exit(1);
		}
}

void 	launch_fight(t_arena *arena)
{
    int j;
//  	init_ncurses(arena);
    //  nprint_arena(arena);
    while (1)
    {
        j = -1;
        while (++j < arena->cycle_to_die)
        {
			ft_printf("boucle cycle : %d\n", j + 1);
            process_champ(arena);
            print_arena(arena);
        }
        arena->nb_live = verif_process(arena, arena->p_head);
		if (!arena->p_head)
			print_winner(arena);
        if ((arena->nb_live >= NBR_LIVE) || (++arena->nb_check >= MAX_CHECKS))
        {
            arena->cycle_to_die -= CYCLE_DELTA;
            arena->nb_check = 0;
        }
    }
}
