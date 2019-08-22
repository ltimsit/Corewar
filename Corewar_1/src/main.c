/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:00:44 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/19 17:37:54 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
int		btohex(char byte);

int		main(int ac, char **av)
{
	(void)ac;
	int fd;
	int i;
	int	ret;
	char	buffer[500];
//	unsigned char test;

	ret = 0;
	fd = open(av[1], O_RDONLY);
	ret = read(fd, buffer, 499);
	buffer[ret] = '\0';
	i = -1;
	while (++i < ret)
	{
		btohex((unsigned char)buffer[i]);
		write(1, " ", 1);
	}
/*
	test = 255;
	btohex(test);
	*/
	return (0);
}
