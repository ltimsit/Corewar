/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrclr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:11:19 by abinois           #+#    #+#             */
/*   Updated: 2019/04/26 14:11:40 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fil_colors(char **color_name, char **color_to_print)
{
	color_name[0] = "red";
	color_name[1] = "green";
	color_name[2] = "yellow";
	color_name[3] = "blue";
	color_name[4] = "magenta";
	color_name[5] = "cyan";
	color_name[6] = "novalidcolor";
	color_to_print[0] = "\033[0;31m";
	color_to_print[1] = "\033[0;32m";
	color_to_print[2] = "\033[0;33m";
	color_to_print[3] = "\033[0;34m";
	color_to_print[4] = "\033[0;35m";
	color_to_print[5] = "\033[0;36m";
}

void			ft_putstrclr(const char *s, const char *color_input)
{
	char	*color_name[7];
	char	*color_to_print[6];
	int		i;

	if (!s || !color_input)
		return ;
	fil_colors(color_name, color_to_print);
	i = 0;
	while (ft_strcmp(color_name[i], color_input) != 0 && i < 6)
		i++;
	if (i > 5)
		ft_putstr("Please chose red, green, yellow, blue, magenta or cyan.");
	else
	{
		ft_putstr(color_to_print[i]);
		ft_putstr(s);
		ft_putstr("\033[0m");
	}
}
