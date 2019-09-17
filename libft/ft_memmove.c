/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:00:52 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:55:44 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dcopy;
	unsigned char	*scopy;

	dcopy = (unsigned char*)dst;
	scopy = (unsigned char*)src;
	if (!len)
		return (dst);
	if (dcopy < scopy)
		return (ft_memcpy(dcopy, scopy, len));
	else
	{
		dcopy = dcopy + (len - 1);
		scopy = scopy + (len - 1);
		while (len--)
			*dcopy-- = *scopy--;
	}
	return (dst);
}
