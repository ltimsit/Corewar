/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 11:58:59 by abinois           #+#    #+#             */
/*   Updated: 2019/05/31 16:37:29 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoinfr(char **s1, char **s2, char option)
{
	char	*new;
	size_t	len;
	int		i;

	new = NULL;
	if (*s1 && *s2)
	{
		len = ft_strlen(*s1) + ft_strlen(*s2);
		if (!(new = (char*)malloc(sizeof(*new) * len + 1)))
			return ((char*)ft_free_stropt(s1, s2, option));
		i = -1;
		while ((*s1)[++i])
			new[i] = (*s1)[i];
		len = 0;
		while ((*s2)[len])
			new[i++] = (*s2)[len++];
		new[i] = '\0';
	}
	ft_free_stropt(s1, s2, option);
	return (new);
}
