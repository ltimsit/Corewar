/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:46:22 by abinois           #+#    #+#             */
/*   Updated: 2019/07/28 13:39:23 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*allocplus(char **buf, char ret, int *x)
{
	int		i;
	int		j;
	char	*buf2;

	i = 0;
	j = 1;
	(*buf)[(*x)] += '0';
	if (--(*x) < 0 && ret == 1)
	{
		while ((*buf)[i])
			i++;
		if (!(buf2 = (char*)malloc(sizeof(char) * ++i + 1)))
		{
			ft_memdel((void**)buf, 0);
			return (NULL);
		}
		buf2[i] = '\0';
		i = 0;
		while ((*buf)[i])
			buf2[j++] = (*buf)[i++];
		ft_memdel((void**)buf, 0);
		buf2[0] = '1';
		return (buf2);
	}
	return (*buf);
}

static char	*move_to_the_end(int *i, int *j, char *s1, char *s2)
{
	char	*buf;
	int		x;

	*i = 0;
	*j = 0;
	while (s1[*i] && s1[*i] != '.')
		(*i)++;
	while (s2[*j] && s2[*j] != '.')
		(*j)++;
	x = (*i) > (*j) ? (*i) : (*j);
	if (!(buf = (char*)malloc(sizeof(char) * x + 1)))
		return ((char*)ft_free_stropt(&s1, &s2, 3));
	buf[x--] = '\0';
	return (buf);
}

char		*ft_str_add(char **s1, char **s2, char option)
{
	int		i;
	int		j;
	int		x;
	char	ret;
	char	*buf;

	if (!(buf = move_to_the_end(&i, &j, *s1, *s2)))
		return (NULL);
	ret = 0;
	x = i-- > j-- ? i : j;
	while (i >= 0 || j >= 0)
	{
		if ((buf[x] = ((i < 0 ? 0 : (*s1)[i--] - '0')
						+ (j < 0 ? 0 : (*s2)[j--] - '0') + ret)) > 9)
		{
			ret = 1;
			buf[x] -= 10;
		}
		else
			ret = 0;
		if (!(buf = allocplus(&buf, ret, &x)))
			break ;
	}
	ft_free_stropt(s1, s2, option);
	return (buf);
}
