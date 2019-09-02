/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:34:46 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/02 14:50:10 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
void	fc_sti(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int elem[3];
	int i;

	ft_printf("YO");
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

void	execute_sti(t_process *process, t_arena *arena)
{
//	ft_printf("data =%d, dest_pc = %d\n", (int)process->data, process->dest_pc);
//	ft_memcpy(&arena->field[process->dest_pc], (char *)&process->data, 4);
	ft_printf("fjdkjshjkshgkjdfhg\n");
	ft_printf("{yellow}%.4x %.4x\n{reset}", process->param.data, process->param.dest_pc);
	put_param_in_field(arena, process->param.data, 4, process->param.dest_pc);
}
