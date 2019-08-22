/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:35:26 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/21 15:21:42 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_alloc_gc(int size, int size_type, t_gc **curr_gc, t_gc **head_gc)
{
	t_gc	*new_gc;

	if (!(new_gc = malloc(sizeof(t_gc))))
		return (NULL);
	if (!*curr_gc)
	{
		(*curr_gc) = new_gc;
		*head_gc = new_gc;
	}
	else
	{
		(*curr_gc)->next = new_gc;
		(*curr_gc) = new_gc;
	}
	new_gc->next = NULL;
	if (!(new_gc->ptr = malloc(size_type * size)))
		return (NULL);
	return (new_gc->ptr);
}
