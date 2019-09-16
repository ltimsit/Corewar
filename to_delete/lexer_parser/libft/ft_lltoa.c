/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:59:28 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/03 16:26:31 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_count(long long nbr)
{
	int		x;

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

char			*ft_lltoa(long long nbr)
{
	long long	res;
	int			neg;
	char		*tab;
	int			n;

	if (nbr == -9223372036854775807 - 1)
	{
		if (!(tab = ft_strdup("-9223372036854775808")))
			return (NULL);
		return (tab);
	}
	n = ft_count(nbr);
	neg = nbr < 0 ? -1 : 1;
	if (!(tab = (char*)malloc(sizeof(*tab) * n + 1)))
		return (NULL);
	res = nbr < 0 ? -nbr : nbr;
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
