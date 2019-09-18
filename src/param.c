/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <abinois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:15:13 by abinois           #+#    #+#             */
/*   Updated: 2019/09/18 19:10:53 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	get_param_code(t_data *data, int p1, int p2, int p3)
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

void	cmd_loop_work(t_data *data, t_param *p, int *pc_cpt, t_op op)
{
	int		i;
	int		cpt;

	cpt = -1;
	p->dir_size = op.dir_size;
	while (++cpt < op.nb_param)
	{
		if (cpt)
			check_separator_char(D, p->cmd);
		go_to_next_elem(D, &D->curr_line, &D->curr_index, 0);
		i = get_elem(D, p->cmd, PARAM_SIZE, SEPARATOR_CHAR);
		p->para[cpt] = get_param_type(D, p, &p->val[cpt], *pc_cpt);
		check_param(D, p->para[cpt], op.param_type[cpt], p->cmd);
		D->curr_index += i;
		p->size_para[cpt] = p->para[cpt] == T_REG ? 1 : 2;
		p->size_para[cpt] = !op.dir_size && p->para[cpt] == T_DIR ? 4
			: p->size_para[cpt];
		*pc_cpt = *pc_cpt + p->size_para[cpt];
	}
}

int		fc_cmd(t_data *data, t_op op)
{
	int		cpt;
	t_param	p;
	int		pc_cpt;

	mem_stock(D, (char*)&(op.opcode), 1);
	cpt = -1;
	ft_bzero(&p, sizeof(t_param));
	pc_cpt = op.ocp ? 1 : 0;
	cmd_loop_work(D, &p, &pc_cpt, op);
	if (op.ocp && (p.ocp = get_param_code(D, p.para[0], p.para[1], p.para[2])))
		mem_stock(D, &p.ocp, 1);
	cpt = -1;
	D->pc += pc_cpt + 1;
	while (++cpt < op.nb_param)
	{
		ft_chen((char *)&(p.val[cpt]), p.size_para[cpt]);
		mem_stock(D, (char *)&(p.val[cpt]), p.size_para[cpt]);
	}
	return (1);
}
