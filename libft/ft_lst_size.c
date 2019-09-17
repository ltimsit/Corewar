/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:38:25 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:02:33 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lst_size(t_list *alst)
{
	t_list	*tmp;
	size_t	size;

	if (!alst)
		return (0);
	size = 1;
	tmp = alst;
	while (tmp->next)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
