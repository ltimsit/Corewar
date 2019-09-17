/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:48:57 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 13:54:05 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "stdlib.h"

void	exit_dis(t_arena *arena)
{
	free_l_process(A);
	exit_fight(A);
	exit(0);
}

void	free_l_process(t_arena *arena)
{
	t_process *tmp;

	while (A->p_head)
	{
		tmp = A->p_head;
		A->p_head = A->p_head->next;
		free(tmp);
	}
}
void	exit_fight(t_arena *arena)
{
	ft_free_gc(A->gc);
	ft_memdel((void**)A->gc, 0);
	exit(EXIT_SUCCESS);
}

