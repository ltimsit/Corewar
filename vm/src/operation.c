/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/18 09:04:27 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		update_pc(int old_pc, int i)
{
	int res;

	res = (old_pc + i) % MEM_SIZE;
	return (res < 0 ? res + MEM_SIZE : res);
}

t_param	fill_param(t_arena *arena, t_op op, t_process *process, int elem[3])
{
	t_param	param;
	int		i;
	int		pc_prev;

	ft_bzero(&param, sizeof(t_param));
	if (op.ocp)
		read_ocp(&param, op.dir_size, A->field[update_pc(PRO->pc, 1)],
				op);
	PRO->pc_next = param.size[0] + param.size[1] + param.size[2] + 1
		+ (op.ocp ? 1 : 0);
	i = -1;
	pc_prev = 0;
	while (++i < op.nb_param)
	{
		stock_in_param(A, &param.value[i], param.size[i],
			update_pc(PRO->pc, 2 + pc_prev));
		if (param.type[i] == REG_CODE && check_reg_num(&param, i))
			elem[i] = chen4(PRO->reg[chen4(param.value[i]) - 1]);
		else if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		else if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(A, PRO, chen4(param.value[i]));
		pc_prev += param.size[i];
	}
	return (param);
}

int		is_valid_type(int param_type, int cmp)
{
	if (cmp == 3 && param_type >= 4)
		return (1);
	if (cmp == 2 && param_type % 4 > 1)
		return (1);
	if (cmp == 1 && param_type % 2)
		return (1);
	return (0);
}

int		is_integer(char *str)
{
	int		len;
	char	signe;

	signe = '+';
	len = ft_strlen(str);
	if (str[0] == '-')
	{
		signe = '-';
		len--;
	}
	if (len > 10)
		return (0);
	else if (len < 10)
		return (1);
	else
	{
		if (signe == '+' && ft_strcmp(str, "2147483647") > 0)
			return (0);
		else if (signe == '-' && ft_strcmp(str + 1, "2147483648") > 0)
			return (0);
		else
			return (1);
	}
}

void	read_ocp(t_param *param, int dir_size, char ocp, t_op op)
{
	int i;
	int j;
	int cmp;
	int	*val;
	int	*type;

	i = 0;
	j = 2;
	val = &param->size[2];
	type = &param->type[2];
	while ((i += 2) < 8)
	{
		cmp = ((ocp >> i) & 3);
		if (j <= op.nb_param - 1 && !is_valid_type(op.param_type[j], cmp))
			param->error = 1;
		if (j <= op.nb_param - 1 && cmp == 1 && (*type = REG_CODE))
			*val = 1;
		else if (j <= op.nb_param - 1 && cmp == 2 && (*type = DIR_CODE))
			*val = dir_size == 1 ? 2 : 4;
		else if (j <= op.nb_param - 1 && cmp == 3 && (*type = IND_CODE))
			*val = 2;
		val--;
		type--;
		j--;
	}
}
