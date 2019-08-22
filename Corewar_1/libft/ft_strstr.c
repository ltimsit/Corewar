/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:47:06 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:14:59 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *str, const char *tofind)
{
	size_t	i;
	size_t	j;

	if (!*tofind)
		return ((char*)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == tofind[j])
		{
			while (str[i + j] == tofind[j] && tofind[j])
				j++;
			if (tofind[j] == '\0')
				return ((char*)str + i);
		}
		i++;
	}
	return (NULL);
}
