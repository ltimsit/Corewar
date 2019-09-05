/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:40:50 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/04 18:39:36 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "mlx.h"
# include "vm.h"
# define BYTE_PER_COL 64
# define W_LEN 1900
# define W_HGT 1900
# define C_LEN 20
# define C_HGT 20
# define P1_COLOR 1
# define P2 2
# define P3 4
# define P4 8


typedef struct	s_display
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*d_img;
}				t_display;

/*
int		display_all(t_display *dis);
int		mouse_press(int button, int x, int y, t_display *dis);
int		key_press(int keycode, t_display *dis);
void	fill_img(char *d_img);
char	*get_data_ptr(void *img_ptr);
*/

#endif
