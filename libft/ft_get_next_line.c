/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:06:58 by abinois           #+#    #+#             */
/*   Updated: 2019/09/13 08:37:27 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft.h"

static int		send_line(char **b, char **b2, char **line)
{
	*line = ft_strsub((const char**)b, 0, *b2 - *b, 0);
	if (!(*b2 = ft_strsub((const char**)b, *b2 - *b + 1, ft_strlen(*b2), 0)))
		return (-1);
	free(*b);
	*b = *b2;
	return (1);
}

int				ft_get_next_line(const int fd, char **line, int o)
{
	static char		*b[OPEN_MAX];
	char			*b2;
	char			tmp[BUFF_SIZE_GNL + 1];
	int				r;

	if ((fd < 0) || (fd > OPEN_MAX) || BUFF_SIZE_GNL < 1 || (!o && !line)
		|| (!o && !b[fd] && !(b[fd] = ft_strnew(0))))
		return (-1);
	r = 0;
	b2 = NULL;
	while (!o && !(ft_strchr(b[fd], '\n'))
		&& (r = read(fd, tmp, BUFF_SIZE_GNL)))
	{
		tmp[r] = '\0';
		if (r == -1 || !(b2 = ft_strjoin(b[fd], tmp)))
			return (-1);
		free(b[fd]);
		b[fd] = b2;
	}
	if (!o && *b[fd] && (b2 = ft_strnchr(b[fd], '\n', r)))
		return (send_line(&(b[fd]), &b2, line));
	else if (!o && *b[fd] && (b2 = ft_strnchr(b[fd], '\0', r)))
		return (send_line(&(b[fd]), &b2, line));
	ft_memdel((void**)&(b[fd]), 0);
	return (0);
}
