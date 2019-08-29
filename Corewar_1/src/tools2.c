/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 12:07:16 by abinois           #+#    #+#             */
/*   Updated: 2019/08/29 14:30:56 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int		skip_comment_block(t_data *data)
{
	int		i;

	while ((i = ft_skip_nochar(D->line, '\n', 0)) != -1)
	{
		D->line += i;
		D->curr_index += i;
		if (*D->line == '\n')
			return (1);
		else if (!(*D->line))
			get_new_read(D);
	}
	return (1);
}
