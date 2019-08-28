/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/28 13:03:28 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

char		get_param_code(t_data *data, int p1, int p2, int p3)
{
	char	code;
	int		tmp;

	(void)data;
	tmp = 0;
	tmp |= (p3 << 2);
	tmp |= (p2 << 4);
	tmp |= (p1 << 6);
	ft_printf("tmp = %bd\n", tmp);
	ft_printf("p1 << 2 = %bd\n", p1 << 2);
	ft_printf("p2 << 4 = %bd\n", p2 << 4);
	ft_printf("p3 << 6 = %bd\n", p3 << 6);
	code = *((char*)(&tmp));
	ft_printf("code %hhu\n", code);
	return (code);
}

int		get_registre(t_data *data, char *cmd)
{
	char reg;
	int i;

	i = 0;
	if (cmd[0] != 'r')
		return (get_error(D, syntax, cmd));
	while (cmd[++i])
		{
			if (!ft_isdigit(cmd[i]))
				return (get_error(D, syntax, cmd));
		}
	if ((reg = ft_atoi(cmd + 1)) < 0
				|| reg > 16)
		return (get_error(D, syntax, cmd));
	mem_stock(D, &reg, 1);
	return (1);
}

int		get_direct4(t_data *data, char *cmd)
{
	int i;
	int direct;

	i = 0;
	if (cmd[0] != DIRECT_CHAR)
		return (get_error(D, syntax, cmd));
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
			return (get_error(D, syntax, cmd));
	}
	direct = ft_atoi(cmd + 1);
	if (!change_endian(D, direct))
		return (0);
	return (1);
}

int		fc_sti(t_data *data, int type, int index)
{
	(void)index;
	char	param;

	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
	param = get_param_code(D, 1, 2, 2);
	if(!mem_stock(D, &param, 1))
			return (0);
	return (1);
}

int		fc_and(t_data *data, int type, int index)
{
//	int 	i;
//	char	cmd[25];
	char	param;

	(void)index;
	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
	param = get_param_code(D, 1, 2, 1);
	if(!mem_stock(D, &param, 1))
			return (0);
//	i = get_elem(D, cmd, 25, SEPARATOR_CHAR);
//	if (!(get_registre(D, cmd)))
//		return (0);
	return (1);
}

int		fc_live(t_data *data, int type, int index)
{
	(void)index;
//	char			cmd[128];
//	unsigned int	direct;
//	int				i;

//	direct = 0;
	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
//	i = get_elem(D, cmd, 128, 0);
//	if (!(get_direct4(D, cmd)))
//		return (0);
//	D->curr_index += i;
	return (1);
}

int		fc_zjmp(t_data *data, int type, int index)
{

	(void)index;
	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
	return (1);
}
