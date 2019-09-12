/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:16:32 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/12 12:09:26 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** RG(source) / RG(source) / RG(dest)
*/

void	fc_add(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, process, elem);
	param.data = elem[0] + elem[1];
	param.dest_pc = param.value[2];
	process->param = param;
}

void	execute_add(t_process *process, t_arena *arena)
{
	(void)A;
	process->carry = !process->param.data ? 1 : 0;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
}

/*
** RG(source) / RG(source) / RG(dest)
*/

void	fc_sub(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];
	int		i;

	i = -1;
	ft_bzero(&param, sizeof(param));
	param = fill_param(A, op, process, elem);
	param.data = elem[0] - elem[1];
	param.dest_pc = param.value[2];
	process->param = param;
}

void	execute_sub(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(process, process->param.data, process->param.dest_pc);
	process->carry = !process->param.data ? 1 : 0;
}
