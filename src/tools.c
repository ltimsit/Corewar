/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:16:38 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 16:13:49 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		skip_sp(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		skip_nosp(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	return (i);
}

void	get_error(t_data *data, int err_type, char *elem)
{
	D->err = err_type;
	print_error(data, elem);
	if (D->gc)
	{
		ft_free_gc(D->gc);
		ft_memdel((void**)D->gc, 0);
	}
	exit(EXIT_FAILURE);
}

void	fill_op_and_err_tab(void)
{
	g_err_tab[0] = "Lexical error";
	g_err_tab[1] = "Syntax error";
	g_err_tab[2] = "Read error !";
	g_err_tab[3] = "Param error";
	g_err_tab[4] = "Missing coma";
	g_err_tab[5] = "Malloc error !";
	g_err_tab[6] = "File error !";
	g_err_tab[7] = "Not enough data at EOF !";
	g_err_tab[8] = "Missing dquote";
}

void	get_error_label(t_data *data, t_label_instr *label, char *name)
{
	ft_printf("{red}No such label{reset} : ");
	ft_printf("[%.3d:%.3d] -> {blink}\"%s\"{reset}\n", 
			label->line, label->col, name);
	if (D->gc)
	{
		ft_free_gc(D->gc);
		ft_memdel((void**)D->gc, 0);
	}
	exit(EXIT_FAILURE);
}
