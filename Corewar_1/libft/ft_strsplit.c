/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:27:47 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:14:41 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_words(const char *s, char c)
{
	int		w;

	w = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			w++;
		while (*s && *s != c)
			s++;
	}
	return (w);
}

static char		**ft_letters(char **tab, const char *s, char c)
{
	size_t	l;
	int		w;

	w = -1;
	while (*s)
	{
		l = 0;
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			w++;
		while (*s && *s != c)
		{
			s++;
			l++;
		}
		tab[w] = ft_strnew(l);
	}
	return (tab);
}

static char		**ft_fill_tab(char **tab, const char *s, char c)
{
	size_t	l;
	int		w;

	w = -1;
	if (!tab)
		return (NULL);
	while (*s)
	{
		l = 0;
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			w++;
		while (*s && *s != c)
			tab[w][l++] = *s++;
	}
	tab[++w] = NULL;
	return (tab);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**tab;
	int		w;

	tab = NULL;
	if (s)
	{
		w = ft_words(s, c);
		tab = (char**)malloc(sizeof(char*) * (w + 1));
	}
	if (!tab)
		return (0);
	tab = ft_letters(tab, s, c);
	tab = ft_fill_tab(tab, s, c);
	return (tab);
}
