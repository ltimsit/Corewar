/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stiplus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:30:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 14:15:40 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int check_param_type(t_data *data, int type, int cmd_param, char *cmd)
{
	if (cmd_param && !(ret = type && cmd_param))
		return (get_error(D, param, cmd));
	return (ret);
}

int param_type_check(t_data *data, char *cmd, int *val)
{
	int value;
	int i;

	i = -1
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
			return (get_error(D, syntax, cmd));
	}
	value == ft_atoi(cmd);
	*val = value;
	return (1);
}

int get_param_type(t_data *data, char *cmd, int *val)
{
	int i;
	int value;
	int ret;

	i = 0;
	if (cmd[0] == DIRECT_CHAR && cmd[1] == LABEL_CHAR)
	{
		if ((*val = check_label(D, cmd + 2)) == -1)
			add_to_label_instr(D, cmd + 2, D->mem_index);
		return (DIR_CODE);
	}
	if ((cmd[0] == 'r' && (ret = REG_CODE))
			|| (cmd[0] == DIRECT_CHAR && (ret = DIR_CODE))
			|| (ret = IND_CODE))
	{
		if (!(param_type_check(D, cmd + (ret == index ? 0 : 1), val)))
			return (get_error(D, syntax, cmd));
		if (ret = registre && value < 0 || reg > 16)
			return (get_error(D, syntax, cmd));
	}
	return (ret);
}
