/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:44:39 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:54:05 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *scopy;

	scopy = (unsigned char*)s;
	if (!n)
		return (NULL);
	while (n--)
	{
		if (*scopy == (unsigned char)c)
			return ((void*)scopy);
		scopy++;
	}
	return (NULL);
}
