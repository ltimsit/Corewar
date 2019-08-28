/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/08/28 20:13:55 by ltimsit-         ###   ########.fr       */
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
	code = *((char*)(&tmp));
	return (code);
}

int		fc_cmd(t_data *data, int type, t_op op)
{
	int		i;
	int		cpt;
	t_param	p;
	int		pc_cpt;

	(void)type;
	if (!mem_stock(D, (char*)&(op.opcode), 1))
		return (0);
	cpt = -1;
	init_param_tab(p.para);
	pc_cpt = op.ocp ? 1 : 0;
	while (++cpt < op.nb_param)
	{
		ft_printf("{red}-- start param --\n{reset}");
		if (cpt && !check_separator_char(D))
			return (0);
		go_to_next_elem(D, &D->curr_line, &D->curr_index);
		i = get_elem(D, p.cmd, PARAM_SIZE, SEPARATOR_CHAR);
		p.para[cpt] = get_param_type(D, p.cmd, &p.val[cpt], pc_cpt);
		ft_printf("param[%d] = %d cmd = %s curr=%c\n", cpt, p.para[cpt], p.cmd, *D->line);
		check_param(D, p.para[cpt], op.param_type[cpt], p.cmd);
		ft_printf("{red}-- end param --\n{reset}");
		D->curr_index += i;
		p.size_para[cpt] = p.para[cpt] == REG_CODE ? 1 : 2;
		p.size_para[cpt] = !op.dir_size && p.para[cpt] == DIR_CODE ? 4 : p.size_para[cpt];
		pc_cpt += p.size_para[cpt];
	}
	if (op.ocp && (p.ocp = get_param_code(D, p.para[0], p.para[1], p.para[2])))
		if (!mem_stock(D, &p.ocp, 1))
			return (0);
	D->pc += op.ocp ? 2 : 1;
	cpt = -1;
	while (++cpt < op.nb_param)
	{
		D->pc += p.size_para[cpt];
		if (!(change_endian(D, (char *)&(p.val[cpt]), p.size_para[cpt])))
			return (0);
	}
	return (1);
}
