/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:22:54 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:54:25 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dcopy;
	const char	*scopy;

	dcopy = (char*)dst;
	scopy = (char*)src;
	if (n == 0)
		return (dst);
	while (n--)
		*dcopy++ = *scopy++;
	return (dst);
}
