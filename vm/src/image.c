/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:08:44 by abinois           #+#    #+#             */
/*   Updated: 2019/09/18 12:35:33 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	put_image(void *mlx, void *win)
{
	void	*image;
	int		width;
	int		height;

	width = 375;
	height = 262;
	image = mlx_xpm_file_to_image(mlx, "/Users/abinois/Documents/GITHUB/COREWAR/vm/img/zaz_375.xpm", &width, &height);
	mlx_put_image_to_window(mlx, win, image, 1803, 1074);
	image = mlx_xpm_file_to_image(mlx, "/Users/abinois/Documents/GITHUB/COREWAR/vm/img/corewar1.xpm", &width, &height);
	mlx_put_image_to_window(mlx, win, image, 1817, 40);
	return (1);
}
