/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_to_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:00:30 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/05 14:13:35 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		btohex(unsigned char byte)
{
	char			*base;
	int				size;
	unsigned char	nb;
	unsigned char	hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = byte;
	while (nb / 16)
	{
		size++;
		nb = nb / 16;
	}
	hex[size] = '\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
	ft_printf("%s", hex);
	return (1);
}
