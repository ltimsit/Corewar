/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:06:23 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 12:17:42 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*suppr;

	if (!alst || !del || !*alst)
		return ;
	tmp = *alst;
	while (tmp)
	{
		suppr = tmp;
		tmp = tmp->next;
		del(suppr->content, suppr->content_size);
		free(suppr);
	}
	*alst = NULL;
}
