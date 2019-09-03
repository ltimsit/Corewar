/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/03 15:48:52 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"
#include "include/op.h"

void	init_fct_instr_tab()
{
	g_fct_instr[0] = NULL;
	g_fct_instr[0x01] = fc_live;
	g_fct_instr[0x02] = fc_ld;
	g_fct_instr[0x03] = fc_st;
	g_fct_instr[0x04] = fc_add;
	g_fct_instr[0x05] = fc_sub;
	g_fct_instr[0x06] = fc_and;
	g_fct_instr[0x09] = fc_zjump;
	g_fct_instr[0x0A] = fc_ldi;
	g_fct_instr[0x0B] = fc_sti;
	g_fct_instr[0x0D] = fc_lld;
	g_fct_instr[0x0E] = fc_lldi;
	g_fct_exec[0x01] = execute_live;
	g_fct_exec[0x02] = execute_ld;
	g_fct_exec[0x03] = execute_st;
	g_fct_exec[0x04] = execute_add;
	g_fct_exec[0x05] = execute_sub;
	g_fct_exec[0x06] = execute_and;
	g_fct_exec[0x09] = execute_zjump;
	g_fct_exec[0x0A] = execute_ldi;
	g_fct_exec[0x0B] = execute_sti;
	g_fct_exec[0x0D] = execute_lld;
	g_fct_exec[0x0E] = execute_lldi;
}

void	read_instruction(t_arena *arena, t_process *process, char opcode)
{
	init_fct_instr_tab();
//	ft_printf("opcode :%d",opcode);
//	ft_printf("%s",op_tab[1].name);
//	fc_sti(
	g_fct_instr[(int)opcode](arena->op[(int)opcode - 1], process, arena);
//	ft_printf("{red}todo = %d{reset}\n", process->c_todo);
}

/*
void		fill_elem(t_arena *arena, t_process *process, int nb_elem, int elem[3])
{
	int i;

	i = -1;
	while (++i < nb_elem)
	{
		if (process->param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(process->param.value[i])];
		if (process->param.type[i] == DIR_CODE)
			elem[i] = process->param.value[i];
		if (process->param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, process->param.value[i]);
	ft_printf("{blue}elem[i] = %d\n{reset}", elem[i]);
	}
}
*/

t_param		fill_param(t_arena *arena, t_op op, t_process *process, int elem[3])
{
	t_param param;
	int i;
	int pc_prev;
	
	ft_bzero(&param, sizeof(param));
	if (op.ocp)
		read_ocp(&param, op.dir_size, arena->field[update_pc(process->pc, 1)], op.param_type);
	process->c_todo = op.time;
	process->pc_next = param.size[0] + param.size[1]
		+ param.size[2] + 1 + (op.ocp ? 1 : 0);
/*
	stock_in_param(arena, &param.value[0], param.size[0], update_pc(process->pc, 2));
	stock_in_param(arena, &param.value[1], param.size[1], update_pc(process->pc, 2 + param.size[0]));
	stock_in_param(arena, &param.value[2], param.size[2],
			update_pc(process->pc, 2 + param.size[0] + param.size[1]));
	*/
	i = -1;
	pc_prev = 0;
	while (++i < op.nb_param)
	{
	stock_in_param(arena, &param.value[i], param.size[i], update_pc(process->pc, 2 + pc_prev));
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i]) - 1];
		if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param.value[i]);
		pc_prev += param.size[i];
	}
	return (param);
}

void	read_ocp(t_param *param, int dir_size, char ocp, int param_type[3])
{
	int i;
	int j;
	int mask;
//	t_ocp new_ocp;
	int cmp;
	int	*val;
	int	*type;

	mask = 3;
	i = 2;
	j = 2;
	val = &param->size[2];
	type = &param->type[2];
	while (i < 8)
	{
		cmp = ((ocp >> i) & mask);
//		ft_printf("{green}{rev}cmp = %bd\ntype = %bd\n{reset}", cmp, param_type[j]);
		if (!(param_type[j] & cmp))
		{
			param->error = 1;
	//		ft_printf("HHHHHHHHHHHHHHHH\n");
	//		return ;
		}
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
		j--;
	}
//	ft_printf("--- %d %d %d ---\n", new_ocp.param1, new_ocp.param2, new_ocp.param3);
}
