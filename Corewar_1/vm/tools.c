/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:01:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/01 14:54:25 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	stock_in_param(t_arena *arena, int *param, int size, int pc)
{
	int id_start;
	char *param_c;

	ft_printf("pc = %d\n", pc);
	param_c = (char *)param;
	id_start = 4 - size;
	while (id_start < 4)
	{
		ft_printf("%.2hhx - ", arena->field[pc]);
		param_c[id_start++] = arena->field[pc++];
		pc %= 4096;
	}
}

void put_param_in_field(t_arena *arena, int param, int size, int pc)
{
	int id_start;
	char *param_c;

	param_c = (char *)&param;
	id_start = 4 - size;
	while (id_start < 4)
	{
		arena->field[pc++] = param_c[id_start++]; 
		pc %= 4096;
	}
}
