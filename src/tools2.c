/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 12:07:16 by abinois           #+#    #+#             */
/*   Updated: 2019/09/11 15:05:29 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			skip_comment_block(t_data *data)
{
	int		i;

	while ((i = ft_skip_nochar(D->line, '\n', 0)) != -1)
	{
		D->line += i;
		D->curr_index += i;
		if (*D->line == '\n')
			return (1);
		else if (!(*D->line))
			if (!(get_new_read(D)))
				return (0);
	}
	return (1);
}

int			check_in_label_char(t_data *data, char *elem)
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

int			check_label(t_data *data, char *elem)
{
	t_label_add *tmp;

	tmp = D->label->head_add;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, elem))
			return (calc_val_from_pc(D->pc, tmp->pc));
		tmp = tmp->next;
	}
	return (-1);
}

int			get_elem(t_data *data, char *tab, int tab_size, char sep_char)
{
	int i;

	i = 0;
	while (i < tab_size && *D->line != ' ' && *D->line != '\t'
			&& *D->line != '\n')
	{
		if (!*D->line)
		{
			if (!(get_new_read(data)))
			{
				tab[i] = '\0';
				return (0);
			}
			continue ;
		}
		if (sep_char && *D->line == sep_char)
			break ;
		tab[i++] = *(D->line)++;
	}
	tab[i] = '\0';
	return (i);
}
