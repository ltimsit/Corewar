/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:28:34 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:11:03 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1copy;
	unsigned char	*s2copy;

	s1copy = (unsigned char*)s1;
	s2copy = (unsigned char*)s2;
	if (!n)
		return (0);
	while (--n && (*s1copy == *s2copy) && *s1copy && *s2copy)
	{
		s1copy++;
		s2copy++;
	}
	return (*s1copy - *s2copy);
}
