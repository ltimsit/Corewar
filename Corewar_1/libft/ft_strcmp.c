/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:39:59 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:03:56 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1copy;
	unsigned char	*s2copy;

	s1copy = (unsigned char*)s1;
	s2copy = (unsigned char*)s2;
	while (*s1copy == *s2copy && *s1copy && *s2copy)
	{
		s1copy++;
		s2copy++;
	}
	return (*s1copy - *s2copy);
}
