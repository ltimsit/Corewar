/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/02 14:44:21 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"
#include "include/op.h"

void	init_fct_instr_tab()
{
	g_fct_instr[0] = NULL;
	g_fct_instr[1] = fc_live;
	g_fct_instr[0x06] = fc_and;
	g_fct_instr[0x0b] = fc_sti;
	g_fct_exec[0x01] = execute_live;
	g_fct_exec[0x0b] = execute_sti;
	g_fct_exec[0x06] = execute_and;
}

void	read_instruction(t_arena *arena, t_process *process, char opcode)
{
	init_fct_instr_tab();
//	ft_printf("opcode :%d",opcode);
//	ft_printf("%s",op_tab[1].name);
//	fc_sti(
	g_fct_instr[(int)opcode](arena->op[(int)opcode - 1], process, arena);
	ft_printf("{red}todo = %d{reset}\n", process->c_todo);
}

t_param		fill_param(t_arena *arena, t_op op, t_process *process)
{
	t_param param;
	
	ft_bzero(&param, sizeof(param));
	if (op.ocp)
		read_ocp(&param, op.dir_size, arena->field[update_pc(process->pc, 1)]);
	process->c_todo = op.time;
	process->pc_next = param.size[0] + param.size[1]
		+ param.size[2] + 1 + (op.ocp ? 1 : 0);
//	ft_printf("ocp1 :%d , ocp2 :%d, ocp3:%d \n", param.size[0], param.size[1], param.size[2]);
	stock_in_param(arena, &param.value[0], param.size[0], update_pc(process->pc, 2));
	stock_in_param(arena, &param.value[1], param.size[1], update_pc(process->pc, 2 + param.size[0]));
	stock_in_param(arena, &param.value[2], param.size[2],
			update_pc(process->pc, 2 + param.size[0] + param.size[1]));
	return (param);
}

void	read_ocp(t_param *param, int dir_size, char ocp)
{
	int i;
	int mask;
//	t_ocp new_ocp;
	int cmp;
	int	*val;
	int	*type;

	mask = 3;
	i = 2;
	val = &param->size[2];
	type = &param->type[2];
	while (i < 8)
	{
		cmp = ((ocp >> i) & mask);
		if (cmp == 1)
		{
			*val = 1;
			*type = REG_CODE;
		}
		if (cmp == 2)
		{
			*val = dir_size == 1 ? 2 : 4;
			*type = DIR_CODE;
		}
		if (cmp == 3)
		{
			*val = 2;
			*type = IND_CODE;
		}
		i += 2;
		val--;
		type--;
	}
//	ft_printf("--- %d %d %d ---\n", new_ocp.param1, new_ocp.param2, new_ocp.param3);
}
