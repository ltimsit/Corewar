/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:30:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/05/09 14:08:53 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

void	ft_display_file(char *file_name)
{
	int		fd;
	int		ret;
	char	buf[1];

	if (!file_name || (fd = open(file_name, O_RDONLY)) == -1)
		return ;
	while ((ret = read(fd, buf, 4096)) && ret != -1)
		write(1, buf, ret);
	close(fd);
}
