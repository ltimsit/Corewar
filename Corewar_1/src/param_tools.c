/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:30:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 17:05:50 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_separator_char(t_data *data)
{
	go_to_next_elem(D, &D->curr_line, &D->curr_index);
	if (*D->line != SEPARATOR_CHAR)
		return (get_error(D, coma, NULL));
	else
	{
		D->line++;
		D->curr_index++;
	}
	return (1);
}

void	init_param_tab(int *params)
{
	params[0] = 0;
	params[1] = 0;
	params[2] = 0;
}

int		check_param(t_data *data, int type, int cmd_param, char *cmd)
{
	int ret;

	ret = 0;
	if (cmd_param && !(ret = type & cmd_param))
		return (get_error(D, param, cmd));
	return (ret);
}

int		param_type_tool(t_data *data, char *cmd, int *val)
{
	int 	value;
	int 	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
			return (get_error(D, syntax, cmd));
	}
	value = ft_atoi(cmd);
	*val = value;
	return (1);
}

int		get_param_type(t_data *data, char *cmd, int *val)
{
	int		i;
	int 	ret;

	i = 0;
	ret = 0;
	if (cmd[0] == DIRECT_CHAR && cmd[1] == LABEL_CHAR)
	{
		if ((*val = check_label(D, cmd + 2)) == -1)
			add_to_label_instr(D, cmd + 2, D->mem_stock_index);
		return (DIR_CODE);
	}
	if ((cmd[0] == 'r' && (ret = REG_CODE))
			|| (cmd[0] == DIRECT_CHAR && (ret = DIR_CODE))
			|| (ret = IND_CODE))
	{
		if (!(param_type_tool(D, cmd + (ret == IND_CODE ? 0 : 1), val)))
			return (get_error(D, syntax, cmd));
		if (ret == REG_CODE && (*val < 0 || ret > 16))
			return (get_error(D, syntax, cmd));
	}
	return (ret);
}
