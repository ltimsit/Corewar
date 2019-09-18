/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:08:44 by abinois           #+#    #+#             */
/*   Updated: 2019/09/18 19:33:54 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		put_image(t_arena *arena)
{
	mlx_put_image_to_window(A->dis->mlx, A->dis->win,
			A->dis->zaz_xpm_img, 1803, 1074);
	mlx_put_image_to_window(A->dis->mlx, A->dis->win,
			A->dis->corewar_xpm_img, 1817, 40);
	return (1);
}

char	*get_path(t_arena *arena, char *path, char *name)
{
	ft_strcpy(path, A->path);
	ft_strcat(path, name);
	return (path);
}

int		init_xpm(t_arena *arena)
{
	int		h;
	int		l;
	char	path[256];

	if (!(A->dis->zaz_xpm_img = mlx_xpm_file_to_image(A->dis->mlx,
					get_path(A, path, "/img/zaz_375.xpm"), &l, &h))
			|| !ft_add_to_gc(A->dis->zaz_xpm_img, A->gc)
			|| !(A->dis->corewar_xpm_img = mlx_xpm_file_to_image(A->dis->mlx,
					get_path(A, path, "/img/corewar1.xpm"), &l, &h))
			|| !ft_add_to_gc(A->dis->corewar_xpm_img, A->gc)
			|| !(A->dis->bulle_xpm_img = mlx_xpm_file_to_image(A->dis->mlx,
					get_path(A, path, "/img/bulle2.xpm"), &l, &h))
			|| !ft_add_to_gc(A->dis->bulle_xpm_img, A->gc))
		return (0);
	return (1);
}
