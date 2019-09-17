/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:29:54 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/05 14:20:01 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_bitoa(void *input, size_t size)
{
	uint8_t	*nb;
	char	*binary;
	uint8_t	mask;

	size = size * 9 - 1;
	nb = (uint8_t*)input;
	if (!(binary = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	binary[size] = '\0';
	while (size)
	{
		mask = 1;
		while (mask)
		{
			binary[--size] = mask & *nb ? '1' : '0';
			mask <<= 1;
		}
		if (size)
			binary[--size] = ' ';
		nb++;
	}
	return (binary);
}
