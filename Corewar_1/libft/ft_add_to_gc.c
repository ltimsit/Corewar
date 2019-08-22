/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:48:13 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/21 15:22:00 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int		ft_add_to_gc(void *ptr, t_gc **curr_gc, t_gc **head_gc)
{
	t_gc	*new_gc;

	if (!(new_gc = malloc(sizeof(t_gc))))
		return (0);
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
	new_gc->ptr = ptr;
	return (1);
}
