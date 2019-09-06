/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fili.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:02:18 by abinois           #+#    #+#             */
/*   Updated: 2019/05/10 19:28:17 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fili(const char *file, size_t line)
{
	ft_putstrclr(file, "green");
	ft_putstr(" > line : ");
	ft_putnbr(line);
	ft_putchar('\n');
}
