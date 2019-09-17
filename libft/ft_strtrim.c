/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:49:20 by abinois           #+#    #+#             */
/*   Updated: 2019/05/31 18:36:26 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (len != i)
	{
		while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
			len--;
	}
	return (ft_strsub((const char**)&s, i, len - i, 0));
}
