/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 12:09:38 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	read_instr(t_arena *arena, t_process *process, char opcode)
{
	g_fct_instr[(int)opcode](A->op[(int)opcode - 1], process, A);
}

t_param	fill_param(t_arena *arena, t_op op, t_process *process, int elem[3])
{
	t_param	param;
	int		i;
	int		pc_prev;

	ft_bzero(&param, sizeof(t_param));
	if (op.ocp)
		read_ocp(&param, op.dir_size, A->field[update_pc(process->pc, 1)],
				op.param_type);
	process->pc_next = param.size[0] + param.size[1] + param.size[2] + 1
		+ (op.ocp ? 1 : 0);
	i = -1;
	pc_prev = 0;
	while (++i < op.nb_param)
	{
		stock_in_param(A, &param.value[i], param.size[i],
			update_pc(process->pc, 2 + pc_prev));
		if (param.type[i] == REG_CODE && check_reg_num(&param, i))
			elem[i] = chen4(process->reg[chen4(param.value[i]) - 1]);
		else if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		else if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(A, process, chen4(param.value[i]));
		pc_prev += param.size[i];
	}
	return (param);
}

void	read_ocp(t_param *param, int dir_size, char ocp, int param_type[3])
{
	int i;
	int j;
	int cmp;
	int	*val;
	int	*type;

	i = 2;
	j = 2;
	val = &param->size[2];
	type = &param->type[2];
	while (i < 8)
	{
		cmp = ((ocp >> i) & 3);
		if (param_type[j] && !(param_type[j] & cmp))
			param->error = 1;
		if (cmp == 1)
		{
			*val = 1;
			*type = REG_CODE;
		}
		else if (cmp == 2)
		{
			*val = dir_size == 1 ? 2 : 4;
			*type = DIR_CODE;
		}
		else if (cmp == 3)
		{
			*val = 2;
			*type = IND_CODE;
		}
		i += 2;
		val--;
		type--;
		j--;
	}
}
