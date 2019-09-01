/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:03:02 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/01 12:48:17 by avanhers         ###   ########.fr       */
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
	t_ocp	ocp;

	ocp = read_ocp(1, arena->field[update_pc(process->pc, 1)]);
	process->c_todo = op.time;
	process->pc_next = ocp.param1 + ocp.param2 + ocp.param3 + 1 + op.ocp ? 1 : 0;
	ft_printf("data %x\n", process->data[2]);
	ft_printf("ocp1 :%d , ocp2 :%d, ocp3:%d \n", ocp.param1, ocp.param2, ocp.param3);
	ft_printf("%d",process->dest_pc);

	ft_memcpy((char*)&process->param1, &arena->field[update_pc(process->pc, 2)], ocp.param1);
	ft_memcpy((char*)&process->param2 , &arena->field[update_pc(process->pc, 2 + ocp.param1)], ocp.param2);
	
	ft_memcpy((char*)&process->param3, &arena->field[update_pc(process->pc, 2 + ocp.param1 + ocp.param2)], ocp.param3);
	ft_memcpy(&process->data, (char *)&process->reg[process->param1], 4);
	
	process->param2= change_endian(process->param2);
	process->param3= process->param3 >>	8;
	process->dest_pc = update_pc(process->pc, process->param2 + process->param3);
	ft_printf("param 1 :%d , param 2:%hd , param 3:%hd , dest :%d\n", process->param1
			,process->param2, process->param3, process->dest_pc);
	ft_printf("param 1 :%#x , param 2:%#x , param 3:%#x , dest :%#x  data: %d\n", process->param1
			,process->param2, process->param3, process->dest_pc, (int)(*process->data));
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
	ft_memcpy(&arena->field[process->dest_pc], &process->data, 4);
}

t_ocp	read_ocp(int dir_size, char ocp)
{
	int i;
	int mask;
	t_ocp new_ocp;
	int cmp;
	int	*val;

	mask = 3;
	i = 2;
	val = &new_ocp.param3;
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
	return (new_ocp);
	ft_printf("--- %d %d %d ---\n", new_ocp.param1, new_ocp.param2, new_ocp.param3);
}
