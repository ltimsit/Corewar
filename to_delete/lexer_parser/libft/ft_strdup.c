/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:35:47 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:05:05 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(*dest) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}
