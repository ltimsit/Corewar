/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/01 15:18:31 by ltimsit-         ###   ########.fr       */
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


void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	read_ocp(&param, 1, arena->field[update_pc(process->pc, 1)]);
	process->c_todo = op.time;
	process->pc_next = param.size[0] + param.size[1]
		+ param.size[2] + 1 + op.ocp ? 1 : 0;
	ft_printf("data %x\n", param.data);
	ft_printf("ocp1 :%d , ocp2 :%d, ocp3:%d \n", param.size[0], param.size[1], param.size[2]);


	stock_in_param(arena, &param.value[0], 1, update_pc(process->pc, 2));
	stock_in_param(arena, &param.value[1], 2, update_pc(process->pc, 2 + param.size[0]));
	stock_in_param(arena, &param.value[2], 2,
			update_pc(process->pc, 2 + param.size[0] + param.size[1]));
	param.data = change_endian(process->reg[change_endian(param.value[0]) - 1]);
	ft_printf("re[0] = %d\n", process->reg[0]);
	
	param.dest_pc = update_pc(process->pc, change_endian(param.value[1] + param.value[2]));
	ft_printf("param 1 :%d , param 2:%hd , param 3:%hd , dest :%d\n", param.value[0]
			, param.value[1], param.value[2], param.dest_pc);
	ft_printf("param 1 :%.2x , param 2:%.2x , param 3:%.2x , dest :%.2x\n", param.value[0]
			, param.value[1], param.value[2], param.dest_pc);
	process->param = param;
}

void	init_fct_instr_tab()
{
	g_fct_instr[0] = NULL;
//	g_fct_instr[1] = fc_live;
	g_fct_instr[0x0b] = fc_sti;
}
void	read_instruction(t_arena *arena, t_process *process, char opcode)
{
	init_fct_instr_tab();
//	ft_printf("opcode :%d",opcode);
//	ft_printf("%s",op_tab[1].name);
//	fc_sti(
	g_fct_instr[(int)opcode](op_tab[(int)opcode - 1], process, arena);
}

void	execute_sti(t_process *process, t_arena *arena)
{
//	ft_printf("data =%d, dest_pc = %d\n", (int)process->data, process->dest_pc);
//	ft_memcpy(&arena->field[process->dest_pc], (char *)&process->data, 4);
	ft_printf("fjdkjshjkshgkjdfhg\n");
	put_param_in_field(arena, process->param.data, 4, process->param.dest_pc);
}

void	read_ocp(t_param *param, int dir_size, char ocp)
{
	int i;
	int mask;
	t_ocp new_ocp;
	int cmp;
	int	*val;

	mask = 3;
	i = 2;
	val = &param->size[2];
	while (i < 8)
	{
		cmp = ((ocp >> i) & mask);
		if (cmp == 1)
			*val = 1;
		if (cmp == 2)
			*val = dir_size == 1 ? 2 : 4;
		if (cmp == 3)
			*val = 2;
		i += 2;
		val--;
	}
	ft_printf("--- %d %d %d ---\n", new_ocp.param1, new_ocp.param2, new_ocp.param3);
}
