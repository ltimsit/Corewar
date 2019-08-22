/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:43:17 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:54:13 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1copy;
	unsigned char	*s2copy;

	s1copy = (unsigned char*)s1;
	s2copy = (unsigned char*)s2;
	while (n--)
	{
		if (*s1copy != *s2copy)
			return (*s1copy - *s2copy);
		s1copy++;
		s2copy++;
	}
	return (0);
}
