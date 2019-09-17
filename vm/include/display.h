/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:40:50 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 14:03:49 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "mlx.h"
# include "vm.h"

# define BYTE_PER_COL		64
# define W_LEN				2200
# define W_HGT				1375
# define C_LEN				20
# define C_HGT				20
# define X_OFFSET			40
# define Y_OFFSET			40

# define HEX_COLOR			0x8c8c8c
# define BORDER_COLOR		0x33cc99
# define BACKGROUND_COLOR	0x123456
# define WHITE				0xffffff
# define ORDER				0xff704c
# define ASSEMBLY			0x9159af
# define ALLIANCE			0x34cf7f
# define FEDERATION			0x488edf


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
	void		*curr_process_dis;
}				t_display;

#endif
