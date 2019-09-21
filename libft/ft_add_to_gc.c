/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:48:13 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/21 15:35:48 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int		ft_add_to_gc(void *ptr, t_gc *gc)
{
	t_gcl	*new_gc_list;

	if (!ptr || !(new_gc_list = malloc(sizeof(t_gcl))))
	{
		ft_memdel((void **)&ptr, 0);
		return (0);
	}
	if (!gc->list)
	{
		(gc->list) = new_gc_list;
		gc->head = new_gc_list;
	}
	else
	{
		(gc->list)->next = new_gc_list;
		(gc->list) = new_gc_list;
	}
	new_gc_list->next = NULL;
	new_gc_list->ptr = ptr;
	return (1);
}
