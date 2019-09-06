/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:26:27 by abinois           #+#    #+#             */
/*   Updated: 2019/05/02 13:19:30 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int		result;
	int		square;

	result = 0;
	square = 0;
	if (nb < 0)
		return (0);
	if (nb < 2)
		return (nb);
	while (square < nb)
	{
		result++;
		square = result * result;
	}
	if (square == nb)
		return (result);
	else
		return (result - 1);
}
