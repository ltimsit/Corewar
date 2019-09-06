/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:25:02 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/03 16:22:55 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_ncurses(t_arena *arena)
{
	if (!arena->ncurses)
		return ;
	initscr();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(PLAYER_1, COLOR_YELLOW, COLOR_GREEN);
	init_pair(PLAYER_2, COLOR_YELLOW, COLOR_GREEN);
	init_pair(PLAYER_3, COLOR_YELLOW, COLOR_GREEN);
	init_pair(PLAYER_4, COLOR_YELLOW, COLOR_GREEN);
}

void nprint_arena(t_arena *arena)
{
	int i;
	int line;
	int col;

	if (!arena->ncurses)
		return ;
	i = -1;
	line = 0;
	col = 0;
	clear();
	while (++i < MEM_SIZE)
	{
		nbtohex(arena->field[i], line, col);
		if (col != COLS - CMENU - 2)
			mvaddch(line, col + 2, ' ');
		if (col >= COLS - CMENU - 2)
		{
			line++;
			col = 0;
		}
		else
			col += 3;
	}
}

void	n_print_reg(t_process *process, t_arena *arena, int reg_nb)
{
	int col;
	int line;
	int i;
	(void)arena;

	if (!arena->ncurses)
		return ;
	i = -1;
	col = COLS - CMENU + 3;
	line = reg_nb;
	while (++i < 4)
	{
		nbtohex(((char *)&process->reg[reg_nb])[i], line, col);
		col += 3;
	}
}

int		pc_to_line_col(int pc, int option)
{
	if (!option)
	{
		return (pc / ((COLS - CMENU) / 3));
	}
	else
		return ((pc % (COLS - CMENU)) * 3);
}

void	n_print_op_exec(int pc, int size, t_arena *arena)
{
	int i;

	if (!arena->ncurses)
		return ;
	i = -1;
	while (++i < size)
		nbtohex(arena->field[pc + i], pc_to_line_col(pc + i, 0), pc_to_line_col(pc + i, 1));
}

void	n_print_pc(int pc, t_arena *arena, int o)
{
	if (!arena->ncurses)
		return ;
	if (!o)
	{
		attron(COLOR_PAIR(1));
		nbtohex(arena->field[pc], pc_to_line_col(pc, 0), pc_to_line_col(pc, 1));
		attroff(COLOR_PAIR(1));
	}
	else
	{
		attron(COLOR_PAIR(0));
		nbtohex(arena->field[pc], pc_to_line_col(pc, 0), pc_to_line_col(pc, 1));
		attroff(COLOR_PAIR(0));
	}
}

int		nbtohex(unsigned char byte, int line, int col)
{
	char *base;
	int	size;
	unsigned char nb;
	char	hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = byte;

	while (nb / 16)
	{
		size++;
		nb = nb / 16;
	}
	if (size == 1)
	{
		hex[0]= '0';
		size++;
	}
	hex[2] ='\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
	mvprintw(line, col, hex);
	refresh();
	return (1);
}
