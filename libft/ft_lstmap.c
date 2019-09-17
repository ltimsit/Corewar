/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:32:54 by abinois           #+#    #+#             */
/*   Updated: 2019/04/12 11:52:14 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	start = f(lst);
	if (start)
	{
		new = start;
		while (lst->next)
		{
			lst = lst->next;
			if (!(new->next = f(lst)))
				return (NULL);
			new = new->next;
		}
	}
	return (start);
}
