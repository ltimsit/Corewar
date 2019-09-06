/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:32:40 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:13:08 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*tofind))
		return ((char*)str);
	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		if (str[i] == tofind[j])
		{
			while (str[i + j] == tofind[j] && tofind[j] && i + j < len)
				j++;
			if (tofind[j] == '\0')
				return ((char*)str + i);
		}
		i++;
	}
	return (NULL);
}
