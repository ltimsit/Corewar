/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:49:24 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:53:11 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*fresh;

	fresh = NULL;
	if (!(fresh = malloc(sizeof(size_t) * size)))
		return (NULL);
	ft_bzero(fresh, size);
	return (fresh);
}
