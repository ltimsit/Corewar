/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/02 14:15:12 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vm.h"
#include "include/op.h"

static t_op	op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

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

void	fc_live(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	process->c_todo = op.time;
	process->pc_next = 5;
	stock_in_param(arena, &param.value[0], 4, update_pc(process->pc, 1));
	param.data = change_endian(param.value[0]);
}
void	fc_and(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[2];
	int i;

	i = 0;
	param = fill_param(arena, op, process);
	while (++i < 2)
	{
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i])];
		if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param, i);
	}
	param.data = elem[0] & elem[1];
	param.dest_pc = -change_endian(param.value[2]);
	process->carry = param.data ? 0 : 1;
	process->param = param;
	ft_printf("{cyan}data = %d{reset}\n", param.data);
	ft_printf("param 1 :%.2x , param 2:%.2x , param 3:%.2x , dest :%.2x\n", param.value[0]
			, param.value[1], param.value[2], param.dest_pc);
}

void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(arena, op, process);
	ft_printf("\ntodo = %d val[0] = %x\n", process->c_todo, param.value[0]);
	while (++i < 3)
	{
		ft_printf("{rev}param type = %d\n{rev}", param.type[i]);
		if (param.type[i] == REG_CODE)
			elem[i] = process->reg[change_endian(param.value[i]) - 1];
		else if (param.type[i] == DIR_CODE)
			elem[i] = param.value[i];
		else if (param.type[i] == IND_CODE)
			elem[i] = fill_index_content(arena, process, param, i);
	}
	ft_printf("elem[0] = %d \n", elem[0]);
	param.data = change_endian(elem[0]);
	ft_printf("re[0] = %d\n", process->reg[0]);
	
	param.dest_pc = update_pc(process->pc, change_endian(elem[1] + elem[2]));
	process->param = param;
	ft_printf("{yellow}%.4x %.4x\n{reset}", process->param.data, process->param.dest_pc);
	ft_printf("{green}pc = %d todo = %d\n{reset}", process->pc_next, process->c_todo);
}

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
	g_fct_instr[(int)opcode](op_tab[(int)opcode - 1], process, arena);
	ft_printf("{red}todo = %d{reset}\n", process->c_todo);
}

void	execute_live(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("le joueur {blue}%s[%d]{reset} a ete declare en vie !\n", "banane", process->param.data);
}

void	execute_sti(t_process *process, t_arena *arena)
{
//	ft_printf("data =%d, dest_pc = %d\n", (int)process->data, process->dest_pc);
//	ft_memcpy(&arena->field[process->dest_pc], (char *)&process->data, 4);
	ft_printf("fjdkjshjkshgkjdfhg\n");
	ft_printf("{yellow}%.4x %.4x\n{reset}", process->param.data, process->param.dest_pc);
	put_param_in_field(arena, process->param.data, 4, process->param.dest_pc);
}

void	execute_and(t_process *process, t_arena *arena)
{
	(void)arena;
	ft_printf("{magenta}fkdjfkd === %d\n{reset}", change_endian(process->param.value[2]));
	put_data_in_reg(process, change_endian(process->param.value[2]));
	ft_printf(" -        -- and fin reg[0] = %d\n", process->reg[0]);
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
