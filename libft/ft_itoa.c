/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:52:42 by abinois           #+#    #+#             */
/*   Updated: 2019/04/23 14:42:56 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static long		ft_count(long nbr)
{
	long	x;

	x = 1;
	if (nbr < 0)
	{
		x++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		x++;
		nbr /= 10;
	}
	return (x);
}

char			*ft_itoa(int nbr)
{
	long	res;
	int		neg;
	char	*tab;
	long	n;

	n = ft_count((long)nbr);
	neg = nbr < 0 ? -1 : 1;
	if (!(tab = (char*)malloc(sizeof(*tab) * n + 1)))
		return (NULL);
	res = nbr < 0 ? -(long)nbr : (long)nbr;
	tab[n] = '\0';
	while (n-- > 0)
	{
		tab[n] = res % 10 + '0';
		res /= 10;
	}
	if (neg == -1)
		tab[0] = '-';
	return (tab);
}
