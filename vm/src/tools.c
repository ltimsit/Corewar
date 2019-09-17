/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:01:14 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 10:34:21 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	chen4(unsigned int little)
{
	unsigned char	t_little[4];
	unsigned char	t_big[4];
	unsigned int	big;
	int				i;

	i = -1;
	ft_memcpy(t_little, &little, sizeof(unsigned int));
	while (++i < 4)
		t_big[i] = t_little[3 - i];
	ft_memcpy(&big, t_big, sizeof(unsigned int));
	return (big);
}

void			stock_in_param(t_arena *arena, int *param, int size, int pc)
{
	int		id_start;
	char	*param_c;

	param_c = (char *)param;
	id_start = 4 - size;
	while (id_start < 4)
	{
		param_c[id_start++] = A->field[pc++];
		pc %= MEM_SIZE;
	}
}

/*
** dest_pc is big_endian
** data is big_endian
*/

void			put_param_in_field(t_arena *arena, t_process *process, int size)
{
	int		id_start;
	char	*param_c;
	int		pc;

	pc = (PRO->pc + chen4(PRO->param.dest_pc)) % 4096;
	param_c = (char *)&PRO->param.data;
	id_start = 4 - size;
	while (id_start < 4)
	{
		A->field[pc] = param_c[id_start++];
		A->carriage[pc] -= A->carriage[pc] % 16;
		A->carriage[pc++] |= 1 << PRO->player_nb;
		pc %= MEM_SIZE;
	}
}

/*
**value is little
*/

int				fill_index_content(t_arena *arena, t_process *process, int val)
{
	int index;
	int	elem;
	int j;

	j = -1;
	index = update_pc(PRO->pc, val);
	while (++j < 4)
	{
		((char *)&elem)[j] = A->field[index++];
		index %= MEM_SIZE;
	}
	return (elem);
}

/*
**data is big_endian
**reg_nb is big_endian
*/

void			put_data_in_reg(t_process *process, int data, int reg_nb)
{
	data = chen4(data);
	reg_nb = chen4(reg_nb);
	reg_nb -= 1;
	if (reg_nb > -1 && reg_nb < 16)
		PRO->reg[reg_nb] = data;
}
