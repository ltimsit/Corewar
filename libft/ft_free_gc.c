/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:37:59 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/13 08:39:26 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_gc(t_gc *gc)
{
	t_gcl	*tmp;

	tmp = gc->head;
	while (gc->head)
	{
		gc->head = gc->head->next;
		if (tmp->ptr)
			ft_memdel((void**)&(tmp->ptr), 0);
		ft_memdel((void**)&tmp, 0);
		tmp = gc->head;
	}
	gc->head = NULL;
	gc->list = NULL;
	return (0);
}
