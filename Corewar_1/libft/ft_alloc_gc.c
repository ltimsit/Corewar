/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:35:26 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/24 15:18:35 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_alloc_gc(int size, int size_type, t_gc *gc)
{
	t_gcl	*new_gc_list;

	if (!(new_gc_list = malloc(sizeof(t_gc))))
		return (NULL);
	if (!gc->list)
	{
		gc->list = new_gc_list;
		gc->head = new_gc_list;
	}
	else
	{
		gc->list->next = new_gc_list;
		gc->list = new_gc_list;
	}
	new_gc_list->next = NULL;
	if (!(new_gc_list->ptr = malloc(size_type * size)))
		return (NULL);
	return (new_gc_list->ptr);
}
