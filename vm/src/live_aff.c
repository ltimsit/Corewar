/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:30:58 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/16 16:53:37 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*g_tab_color[4] =
{
	"orange", "purple", "green", "blue"
};

/*
** D4 (id du joueur)
*/

int		check_valid_champ(int id, t_arena *arena)
{
	int		i;

	i = -1;
	while (++i < A->nb_champ)
		if (A->champ[i].id == id)
		{
			A->champ[i].nb_live++;
			return (i);
		}
	return (-1);
}

void	fc_live(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;

	(void)op;
	ft_bzero(&param, sizeof(t_param));
	process->pc_next = 5;
	stock_in_param(A, &param.value[0], 4, update_pc(process->pc, 1));
	param.data = chen4(param.value[0]);
	process->param = param;
}

void	execute_live(t_process *process, t_arena *arena)
{
	int		i;

	(void)A;
	(void)process;
	process->nb_live += 1;
	if ((i = check_valid_champ(process->param.data, A)) == -1)
		return ;
	A->last_living_champ = process->param.data;
	if (A->dump_cycle == -1)
		ft_printf("Un processus dit que le joueur {%s}%s{reset} est en vie.\n",
				g_tab_color[i], A->champ[i].h.prog_name);
}

void	fc_aff(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	process->pc_next = 3;
	param = fill_param(A, op, process, elem);
	param.data = chen4(elem[0]) % 256;
	process->param = param;
}

void	execute_aff(t_process *process, t_arena *arena)
{
	int	i;

	i = check_valid_champ(process->id_champ, A);
	(void)A;
	if (process->aff_index == AFF_SIZE || !process->param.data)
	{
		ft_printf("{%s}%s\n{reset}", g_tab_color[i], process->aff);
		process->aff_index = 0;
		ft_bzero(process->aff, AFF_SIZE);
	}
	else
		process->aff[process->aff_index++] = process->param.data;
}
