/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:41:29 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/01 19:27:58 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "libft.h"
#include <stdlib.h>

int main()
{
	int i;
	char *val;
	WINDOW *menu;

	initscr();
	refresh();
	i = -1;

//	menu = subwin(stdscr, LINES / 3, COLS / 4, 2, COLS - COLS / 3 - 2);
	box(menu, ACS_VLINE, ACS_HLINE);
//	mvwprintw(menu, 2, 2, "Bonjour");
	while (1)
	{
	clear();
	menu = subwin(stdscr, LINES / 3, COLS / 4, 2, COLS - COLS / 3 - 2);
	box(menu, ACS_VLINE, ACS_HLINE);
	mvprintw(LINES / 2, COLS / 2, "Bonjour");
	refresh();
	if (getch() != 410)
		break ;
	free(menu);
	}
/*
	val = ft_itoa(COLS);
		mvprintw(0, 0, val);
		val = ft_itoa(LINES);
		mvprintw(10, 0, val);
		*/
/*
	while (++i < 700)
	{
		val = ft_itoa(i / COLS);
		mvprintw(i / COLS, i % COLS, val);
	}
	*/
//	getch();
	endwin();
	free(menu);
}
