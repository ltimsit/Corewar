/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:25:21 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:13:22 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*adr;

	adr = NULL;
	if (c < 0)
		return (adr);
	if ((char)c == '\0')
		return (ft_strchr(s, '\0'));
	while (*s != '\0')
	{
		if (*s == (char)c)
			adr = (char*)s;
		s++;
	}
	return ((char*)adr);
}
