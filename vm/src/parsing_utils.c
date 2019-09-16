/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:06:18 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/16 16:54:59 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			check_id(t_arena *arena, char *str)
{
	int i;
	int nb;

	i = -1;
	if (ft_str_is_digit(str) && is_integer(str))
	{
		nb = ft_atoi(str);
		if (nb > 1000 || nb < -1000)
			return (0);
		else
		{
			while (++i < A->nb_champ)
				if (A->champ[i].id == nb)
				{
					ft_error(A, "2 champs with same id");
					return (0);
				}
		}
		return (1);
	}
	return (0);
}

int			is_integer(char *str)
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
