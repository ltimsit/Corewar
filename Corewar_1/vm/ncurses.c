/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:25:02 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/02 16:23:01 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm.h"

void	init_ncurses()
{
	initscr();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_GREEN);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
}

void nprint_arena(t_arena *arena)
{
	int i;
	int line;
	int col;

	i = -1;
	line = 0;
	col = 0;
	clear();
	while (++i < MEM_SIZE)
	{
		nbtohex(arena->field[i], line, col);
		if (col != COLS - 2)
			mvaddch(line, col + 2, ' ');
		if (col == COLS - 2)
		{
			line++;
			col = 0;
		}
		else
			col += 3;
	}
}

int		pc_to_line_col(int pc, int option)
{
	if (!option)
	{
		return (pc / (COLS / 3));
	}
	else
		return ((pc % COLS) * 3);
}

void	n_print_op_exec(int pc, int size, t_arena *arena)
{
	int i;

	i = -1;
	while (++i < size)
		nbtohex(arena->field[pc + i], pc_to_line_col(pc + i, 0), pc_to_line_col(pc + i, 1));
}

void	n_print_pc(int pc, t_arena *arena, int o)
{
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
