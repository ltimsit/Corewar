/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 12:07:16 by abinois           #+#    #+#             */
/*   Updated: 2019/08/29 12:45:47 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int		skip_comment_block(t_data *data)
{
	int		i;

	i = ft_skip_nochar(D->line, '\n', 0);
	D->line += i;
	D->curr_index += i;
	return (i);
}
