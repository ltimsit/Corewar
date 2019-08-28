/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/28 16:05:21 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		get_param_code(t_data *data, int p1, int p2, int p3)
{
	char	code;
	int		tmp;

	(void)data;
	tmp = 0;
	if (p3)
		tmp |= (p3 << 2);
	if (p2)
		tmp |= (p2 << 4);
	if (p1)
		tmp |= (p1 << 6);
	/*
	ft_printf("tmp = %bd\n", tmp);
	ft_printf("p1 << 2 = %bd\n", p1 << 2);
	ft_printf("p2 << 4 = %bd\n", p2 << 4);
	ft_printf("p3 << 6 = %bd\n", p3 << 6);
	*/
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
	int		i;
	int		direct;

	i = 0;
	if (cmd[0] != DIRECT_CHAR)
		return (get_error(D, param, cmd));
/*
	while (cmd[++i])
		if (!ft_isdigit(cmd[i]))
			return (get_error(D, param, cmd));
	*/
	direct = ft_atoi(cmd[1] == ':' ? cmd + 2 : cmd +1);
	if (!change_endian(D, direct))
		return (0);
	return (1);
}

int		fc_cmd(t_data *data, int type, t_op op)
{
	int		i;
	int		cpt;
	t_param	p;

	(void)type;
	if(!mem_stock(D, (char*)&(op.opcode), 1))
		return (0);
	cpt = -1;
	ft_printf("Hello\n");
	init_param_tab(p.para);
	while (++cpt < op.nb_param)
	{
		if (cpt && !check_separator_char(D))
			return (0);
		go_to_next_elem(D, &D->curr_line, &D->curr_index);
		i = get_elem(D, p.cmd, PARAM_SIZE, SEPARATOR_CHAR);
		p.para[cpt] = get_param_type(D, p.cmd, &p.val[cpt]);
		ft_printf("param[%d] = %d cmd = %s curr=%c\n", cpt, p.para[cpt], p.cmd, *D->line);
		check_param(D, p.para[cpt], op.param_type[cpt], p.cmd);
		D->curr_index += i;
	}
	if (op.ocp && (p.ocp = get_param_code(D, p.para[0], p.para[1], p.para[2])))
		if(!mem_stock(D, &p.ocp, 1))
			return (0);
	cpt = -1;
	while (++cpt < op.nb_param)
	{
		i = p.para[cpt] == REG_CODE ? 1 : 2;
		i = !op.dir_size && p.para[cpt] == DIR_CODE ? 4 : 2;
		if (!(mem_stock(D, (char*)&p.val[cpt], i)))
			return (0);
	}
	return (1);
}

/*
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

*/
/*
int		fc_live(t_data *data, int type, int index)
{
	(void)index;
	char			cmd[128];
//	unsigned int	direct;
	int				i;

//	direct = 0;
	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
	go_to_next_elem(D, &D->curr_line, &D->curr_index);
	i = get_elem(D, cmd, 128, 0);
	if (!(get_direct4(D, cmd)))
		return (0);
	D->curr_index += i;
	return (1);
}

int		fc_zjmp(t_data *data, int type, int index)
{
	char	cmd[128];
	int		i;

	(void)index;
	if(!mem_stock(D, (char*)&(op_tab[type - command_line].opcode), 1))
		return (0);
	go_to_next_elem(D, &D->curr_line, &D->curr_index);
	i = get_elem(D, cmd, 128, 0);
	if (!(get_direct4(D, cmd)))
		return (0);
	D->curr_index += i;
	return (1);
}
*/
