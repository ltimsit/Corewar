/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:26:27 by abinois           #+#    #+#             */
/*   Updated: 2019/08/12 18:09:19 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrtup(int nb)
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
	return (result);
}
