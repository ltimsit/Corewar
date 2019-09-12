/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:18:42 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/12 10:16:18 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_op	g_op_tab[17] =
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

void	set_op_table(t_arena *arena)
{
	int		i;

	i = -1;
	while (++i < 16)
		A->op[i] = g_op_tab[i];
}

void	init_fct_instr_tab(void)
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
	g_fct_instr[0x0F] = fc_lfork;
	g_fct_instr[0x10] = fc_aff;
}

void	init_fct_exec_tab(void)
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
	g_fct_exec[0x0F] = execute_lfork;
	g_fct_exec[0x10] = execute_aff;
}
