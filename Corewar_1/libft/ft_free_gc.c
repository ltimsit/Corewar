/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:37:59 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/26 19:32:23 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_free_gc(t_gc *gc)
{
	t_gcl	*tmp;

	tmp = gc->head;
	while (gc->head)
	{
		gc->head = gc->head->next;
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
		tmp = gc->head;
	}
	gc->head = NULL;
	gc->list = NULL;
	return (0);
}
