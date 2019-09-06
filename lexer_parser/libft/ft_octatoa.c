/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octatoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:46:14 by edillenb          #+#    #+#             */
/*   Updated: 2019/05/15 15:09:42 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_octatoa(unsigned long long nbr)
{
	unsigned long long	res;
	char				*tab;
	int					n;

	res = nbr;
	n = 1;
	while (res > 7)
	{
		n++;
		res /= 8;
	}
	if (!(tab = (char*)malloc(sizeof(*tab) * n + 1)))
		return (NULL);
	tab[n] = '\0';
	while (n-- > 0)
	{
		tab[n] = nbr % 8 + '0';
		nbr /= 8;
	}
	return (tab);
}
