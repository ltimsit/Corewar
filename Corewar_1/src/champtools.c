/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champtools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:55:17 by abinois           #+#    #+#             */
/*   Updated: 2019/08/24 13:26:51 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

char		*stock_namecom(char *line)
{
	int		start;
	int		end;
	char	*namecom;
	
	ft_printf("line=%s\n", line);
	start = ft_skip_nochar(line, '"', 0);
	end = ft_skip_nochar(line + start + 1, '"', 0);
	namecom = ft_strsub((const char **)&line, start + 1, end, 0);
	return (namecom);
}
