/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:06:18 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/16 16:08:48 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	is_integer(char *str)
{
	int		len;
	char	signe;

	signe = '+';
	len = ft_strlen(str);
	if (str[0] == '-')
	{
		signe = '-';
		len--;
	}
	if (len > 10)
		return (0);
	else if (len < 10)
		return (1);
	else
	{
		if (signe == '+' && ft_strcmp(str, "2147483647") > 0)
			return (0);
		else if (signe == '-' && ft_strcmp(str + 1, "2147483648") > 0)
			return (0);
		else
			return (1);
	}
}
