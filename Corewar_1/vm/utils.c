/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:17:25 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/27 15:58:39 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "include/vm.h"
#include <stdlib.h>

void	ft_error(char *message)
{
	ft_putstr(message);
	exit(EXIT_FAILURE);	
}

int		btohex(unsigned char byte)
{
	char *base;
	int	size;
	unsigned char nb;
	unsigned char	hex[3];

	base = "0123456789abcdef";
	size = 1;
	nb = byte;

	while (nb / 16)
	{
		size++;
		nb = nb / 16;
	}
	if (size == 1)
	{
		hex[0]= '0';
		size++;
	}
	hex[2] ='\0';
	while (size--)
	{
		hex[size] = base[byte % 16];
		byte /= 16;
	}
	ft_printf("%s", hex);
	return (1);
}