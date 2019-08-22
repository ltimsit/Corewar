/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:37:59 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/19 16:04:16 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_free_gc(t_gc *head_gc)
{
	t_gc	*tmp;

	tmp = head_gc;
	while (head_gc)
	{
		head_gc = head_gc->next;
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
		tmp = head_gc;
	}
	return (0);
}
