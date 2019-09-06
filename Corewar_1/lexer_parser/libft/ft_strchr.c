/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:39:52 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:02:03 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	if (c < 0)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	return (NULL);
}
