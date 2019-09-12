/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:40:50 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/12 16:18:56 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "mlx.h"
# include "vm.h"
# define BYTE_PER_COL 64
# define W_LEN 2200
# define W_HGT 1900
# define C_LEN 20
# define C_HGT 20
# define P1_COLOR 1
# define P2 2
# define P3 4
# define P4 8
# define HEX_COLOR 0x8c8c8c
# define X_OFFSET 40
# define Y_OFFSET 40
# define BORDER_COLOR 0x33cc99
# define BACKGROUND_COLOR 0x123456

typedef struct	s_display
{
	void		*mlx;
	void		*win;
	void		*img[5];
	void		*border_img;
	char		*d_img[5];
	char		*d_border_img;
	int			speed;
}				t_display;

/*
int		display_all(t_display *dis);
int		mouse_press(int button, int x, int y, t_display *dis);
int		key_press(int keycode, t_display *dis);
void	fill_img(char *d_img);
char	*get_data_ptr(void *img_ptr);
*/
#endif
