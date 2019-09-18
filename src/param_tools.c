/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:30:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/18 16:29:22 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_separator_char(t_data *data, char *cmd)
{
	go_to_next_elem(D, &D->curr_line, &D->curr_index, 0);
	if (*D->line != SEPARATOR_CHAR)
		get_error(D, coma, cmd);
	else
	{
		D->line++;
		D->curr_index++;
	}
	return (1);
}

int		check_param(t_data *data, int type, int cmd_param, char *cmd)
{
	int ret;

	ret = 0;
	if (cmd_param && !((ret = type) & cmd_param))
		get_error(D, param, cmd);
	return (ret);
}

int		param_type_tool(char *cmd, int *val)
{
	int		value;
	int		i;

	i = -1;
	while (cmd[++i])
		if (!ft_isdigit(cmd[i]) && !(i == 0 && cmd[i] == '-'))
			return (0);
	value = ft_atoi(cmd);
	*val = value;
	return (1);
}

int		get_param_type(t_data *data, t_param *p, int *val, int pc_cpt)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if ((p->cmd[0] == DIRECT_CHAR && p->cmd[1] == LABEL_CHAR)
			|| p->cmd[0] == LABEL_CHAR)
	{
		if ((*val = check_label(D, p->cmd +
				(p->cmd[0] == LABEL_CHAR ? 1 : 2))) == -1)
			add_to_label_instr(D, p->cmd + (p->cmd[0] == LABEL_CHAR ? 1 : 2),
					D->mem_stock_index + pc_cpt, p->cmd[0] == LABEL_CHAR ? 1 : p->dir_size);
		return (p->cmd[0] == LABEL_CHAR ? IND_CODE : DIR_CODE);
	}
	if ((p->cmd[0] == 'r' && (ret = REG_CODE))
			|| (p->cmd[0] == DIRECT_CHAR && (ret = DIR_CODE))
			|| (ret = IND_CODE))
	{
		if (!(param_type_tool(p->cmd + (ret == IND_CODE ? 0 : 1), val)))
		{
			ft_printf("champtools 1");
			get_error(D, syntax, p->cmd);
		}
		if (ret == REG_CODE && (*val < 0 || *val > 16))
		{
			ft_printf("champtools 12");
			get_error(D, syntax, p->cmd);
		}
	}
	return (ret);
}
/*
int		get_param_type(t_data *data, char *cmd, int *val, int pc_cpt)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if ((cmd[0] == DIRECT_CHAR && cmd[1] == LABEL_CHAR)
			|| cmd[0] == LABEL_CHAR)
	{
		if ((*val = check_label(D, cmd +
				(cmd[0] == LABEL_CHAR ? 1 : 2))) == -1)
			add_to_label_instr(D, cmd + (cmd[0] == LABEL_CHAR ? 1 : 2),
					D->mem_stock_index + pc_cpt);
		return (cmd[0] == LABEL_CHAR ? IND_CODE : DIR_CODE);
	}
	if ((cmd[0] == 'r' && (ret = REG_CODE))
			|| (cmd[0] == DIRECT_CHAR && (ret = DIR_CODE))
			|| (ret = IND_CODE))
	{
		if (!(param_type_tool(cmd + (ret == IND_CODE ? 0 : 1), val)))
			get_error(D, syntax, cmd);
		if (ret == REG_CODE && (*val < 0 || *val > 16))
			get_error(D, syntax, cmd);
	}
	return (ret);
}*/
