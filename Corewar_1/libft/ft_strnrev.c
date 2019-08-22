/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:49:41 by abinois           #+#    #+#             */
/*   Updated: 2019/04/16 09:28:24 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnrev(char *str, size_t len)
{
	size_t	i;
	size_t	lmax;
	char	buf;

	if (!str || len < 2)
		return (str);
	lmax = ft_strlen(str) - 1;
	len = len > lmax ? lmax : len - 1;
	i = 0;
	buf = 'a';
	while (i < len)
	{
		buf = str[len];
		str[len] = str[i];
		str[i] = buf;
		i++;
		len--;
	}
	return (str);
}
