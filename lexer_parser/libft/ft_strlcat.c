/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:23:51 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:09:50 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lend = ft_strlen(dst);
	lens = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (size + lens);
	while (src[i] && (lend + i) < (size - 1))
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	if (lend >= size)
		return (size + lens);
	return (lend + lens);
}
