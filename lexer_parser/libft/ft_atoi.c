/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:15:03 by abinois           #+#    #+#             */
/*   Updated: 2019/06/05 17:24:52 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_atoi(const char *str)
{
	int			i;
	size_t		result;
	int			negpos;

	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	negpos = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i++] - 48;
		if (result / 10 > 922337203685477580
				|| (result / 10 == 922337203685477580 && result % 10 > 7))
			return (negpos == -1 ? 0 : -1);
	}
	return ((int)result * negpos);
}
