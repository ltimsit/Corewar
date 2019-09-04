/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:37:12 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/04 11:31:05 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

/*
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
*/

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
        ft_printf("%d YOO ID %d", arena->nb_champ, arena->champ[i].id);
        add_process(arena, arena->champ[i].id);
        ft_printf("YOO ID %d", arena->champ[i].id);
        arena->process->pc = i * space;
        ft_printf("YOO ID %d", arena->champ[i].id);
        //  print_process(&arena->champ[i]);
    }
}

void	check_process(t_arena *arena, t_process *process)
{
	char opcode;
	int j;

	ft_printf("{blue}process = %p{reset}\n", process);
	ft_printf("{blue}pc next  = %d{reset}\n", process->pc_next);
	ft_printf("{red}todo = %d\n{reset}", process->c_todo);
	ft_printf("{yellow}done = %d\n{reset}", process->c_done);
	ft_printf("{cyan}opcode = %d\n{reset}", process->opcode);
	if (!process->c_todo)
	{
		ft_printf("{italic}process opcode == %hhd\n{reset}", arena->field[process->pc]);
		if ((opcode = arena->field[process->pc]) > 0 && opcode < 17)
		{
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
		ft_printf("exec ------ r[0] = %d\n", process->reg[0]);
		g_fct_exec[(int)process->opcode](process, arena);
		ft_printf("exec ------ r[0] = %d\n", process->reg[0]);
		n_print_pc(process->pc, arena, 1);
		process->pc = update_pc(process->pc, process->pc_next);
//		ft_printf("{yellow}pc = %d\n{reset}", process->pc);
		process->c_done = 1;
		process->c_todo = 0;
	}
	j = -1;
	while (++j < 17)
	{
		n_print_reg(process, arena, j);
	}
	n_print_pc(process->pc, arena, 0);
//	ft_printf("{blue}process = %p{reset}\n", process);
}

/*
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
*/
void    process_champ(t_arena *arena)
{
    t_process *tmp;
    tmp = arena->p_head;
    while (tmp)
    {
        check_process(arena, tmp);
        tmp = tmp->next;
       ft_printf("{green}tmp->next = %p\n{reset}", tmp);
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
            del_process(arena, tmp, prev);//add prev
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
void launch_fight(t_arena *arena)
{
    int j;
    //  print_arena(arena);
    //  ft_putchar('\n');
//  	init_ncurses(arena);
    //  nprint_arena(arena);
    while (1)
    {
        j = -1;
        while (++j < CYCLE_TO_DIE)
        {
      	  ft_printf("boucle cycle : %d\n", j + 1);
        ft_printf("{green}head = %p\n{reset}", arena->p_head);
            process_champ(arena);
            print_arena(arena);
        }
        arena->nb_live = verif_process(arena, arena->p_head);
        if ((arena->nb_live >= NBR_LIVE) || (++arena->nb_check >= MAX_CHECKS))
        {
            arena->cycle_to_die -= CYCLE_DELTA;
            arena->nb_check = 0;
        }
    }
}





/*
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
*/
