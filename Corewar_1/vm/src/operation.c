/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/05 12:58:26 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_fct_instr_tab()
{
	g_fct_instr[0] = NULL;
	g_fct_instr[0x01] = fc_live;
	g_fct_instr[0x02] = fc_ld;
	g_fct_instr[0x03] = fc_st;
	g_fct_instr[0x04] = fc_add;
	g_fct_instr[0x05] = fc_sub;
	g_fct_instr[0x06] = fc_and;
	g_fct_instr[0x07] = fc_or;
	g_fct_instr[0x08] = fc_xor;
	g_fct_instr[0x09] = fc_zjump;
	g_fct_instr[0x0A] = fc_ldi;
	g_fct_instr[0x0B] = fc_sti;
	g_fct_instr[0x0C] = fc_fork;
	g_fct_instr[0x0D] = fc_lld;
	g_fct_instr[0x0E] = fc_lldi;
//	g_fct_instr[0x0F] = fc_lfork;
//	g_fct_instr[0x10] = fc_aff;
}

void	init_fct_exec_tab()
{
	g_fct_exec[0] = NULL;
	g_fct_exec[0x01] = execute_live;
	g_fct_exec[0x02] = execute_ld;
	g_fct_exec[0x03] = execute_st;
	g_fct_exec[0x04] = execute_add;
	g_fct_exec[0x05] = execute_sub;
	g_fct_exec[0x06] = execute_and;
	g_fct_exec[0x07] = execute_or;
	g_fct_exec[0x08] = execute_xor;
	g_fct_exec[0x09] = execute_zjump;
	g_fct_exec[0x0A] = execute_ldi;
	g_fct_exec[0x0B] = execute_sti;
	g_fct_exec[0x0C] = execute_fork;
	g_fct_exec[0x0D] = execute_lld;
	g_fct_exec[0x0E] = execute_lldi;
//	g_fct_exec[0x0F] = execute_lfork;
//	g_fct_exec[0x10] = execute_aff;
}

void	read_instruction(t_arena *arena, t_process *process, char opcode)
{
//	ft_printf("opcode :%d",opcode);
//	ft_printf("%s",op_tab[1].name);
//	fc_sti(
	g_fct_instr[(int)opcode](arena->op[(int)opcode - 1], process, arena);
//	ft_printf("{red}todo = %d{reset}\n", process->c_todo);
}

t_param		fill_param(t_arena *arena, t_op op, t_process *process, int elem[3])
{
	t_param param;
	int i;
	int pc_prev;
	
	ft_bzero(&param, sizeof(t_param));
	if (op.ocp)
		read_ocp(&param, op.dir_size, arena->field[update_pc(process->pc, 1)], op.param_type);
	process->pc_next = param.size[0] + param.size[1]
		+ param.size[2] + 1 + (op.ocp ? 1 : 0);
	i = -1;
	pc_prev = 0;
	while (++i < op.nb_param)
	{
	stock_in_param(arena, &param.value[i], param.size[i], update_pc(process->pc, 2 + pc_prev));
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i]) - 1];
		if (param.type[i] == DIR_CODE)
			elem[i] = change_endian(param.value[i]);
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
		if (!(param_type[j] & cmp))
		{
			param->error = 1;
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
}
