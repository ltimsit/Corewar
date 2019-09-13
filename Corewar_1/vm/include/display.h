/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:40:50 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/13 11:37:37 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "mlx.h"
# include "vm.h"

# define BYTE_PER_COL		64
# define W_LEN				2200
# define W_HGT				1900
# define C_LEN				20
# define C_HGT				20
# define X_OFFSET			40
# define Y_OFFSET			40

# define P1_COLOR			1
# define P2					2
# define P3					4
# define P4					8
# define HEX_COLOR			0x8c8c8c
# define BORDER_COLOR		0x33cc99
# define BACKGROUND_COLOR	0x123456

typedef struct	s_display
{
	void		*mlx;
	void		*win;
	void		*img[5];
	void		*border_img;
	char		*d_img[5];
	char		*d_border_img;
	int			speed;
	int			cpt_to_speed;
}				t_display;

#endif
