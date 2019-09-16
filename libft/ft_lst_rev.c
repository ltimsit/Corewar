/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:28:37 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:48:13 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_lst_rev(t_list **alst)
{
	t_list	*prev;
	t_list	*next;
	t_list	*current;

	prev = NULL;
	next = NULL;
	if (!alst)
		return (NULL);
	current = *alst;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*alst = prev;
	return (alst);
}
