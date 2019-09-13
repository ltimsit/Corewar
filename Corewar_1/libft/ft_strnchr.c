/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:24:05 by abinois           #+#    #+#             */
/*   Updated: 2019/09/13 08:40:02 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnchr(const char *s, int c, int len)
{
	int		i;

	i = -1;
	if (c < 0)
		return (NULL);
	while (++i < len)
		if (s[i] == (char)c)
			return ((char*)s + i);
	if (s[i] == (char)c)
		return ((char*)s + i);
	return (NULL);
}
