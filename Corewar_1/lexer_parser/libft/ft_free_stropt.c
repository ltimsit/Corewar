/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_stropt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:46:33 by abinois           #+#    #+#             */
/*   Updated: 2019/07/28 13:39:52 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_free_stropt(char **s1, char **s2, char option)
{
	if (option == 1)
		ft_memdel((void**)s1, 0);
	if (option == 2)
		ft_memdel((void**)s2, 0);
	if (option == 3)
	{
		ft_memdel((void**)s1, 0);
		ft_memdel((void**)s2, 0);
	}
	return (NULL);
}
