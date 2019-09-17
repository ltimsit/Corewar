/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:03:02 by abinois           #+#    #+#             */
/*   Updated: 2019/07/28 13:27:02 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_memdel(void **ap, int return_value)
{
	if (!ap || !(*ap))
		return (return_value);
	free(*ap);
	*ap = NULL;
	return (return_value);
}
