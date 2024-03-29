/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:48:57 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 20:02:16 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "stdlib.h"

int		exit_dis(t_arena *arena)
{
	free_l_process(A);
	exit_fight(A);
	return (0);
}

void	free_l_process(t_arena *arena)
{
	t_process *tmp;

	while (A->p_head)
	{
		tmp = A->p_head;
		A->p_head = A->p_head->next;
		ft_memdel((void**)&tmp, 0);
	}
}

void	exit_fight(t_arena *arena)
{
	ft_free_gc(A->gc);
	ft_memdel((void**)&(A->gc), 0);
	exit(EXIT_SUCCESS);
}
