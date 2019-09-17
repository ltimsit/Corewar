/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:16:38 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 19:07:47 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

int		print_usage(void)
{
	ft_printf("{rev}{orange}Usage:{reset}{orange} ./asm <champ.s>\n{reset}");
	return (0);
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
	g_err_tab[6] = "File name too long or no extension !";
	g_err_tab[7] = "Not enough data at EOF !";
	g_err_tab[8] = "Missing dquote";
	g_err_tab[9] = "Open error !";
	g_err_tab[10] = "Close error !";
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

int		check_in_label_char(t_data *data, char *elem)
{
	int		i;
	int		j;
	char	*label_chars;

	label_chars = LABEL_CHARS;
	j = -1;
	while (elem[++j])
	{
		i = -1;
		while (label_chars[++i])
		{
			if (elem[j] == label_chars[i])
				break ;
			if (elem[j] == LABEL_CHAR)
			{
				elem[j] = '\0';
				return (1);
			}
		}
		if (!label_chars[i])
			get_error(D, syntax, elem);
	}
	get_error(D, syntax, elem);
	return (0);
}
