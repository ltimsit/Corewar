/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:40:50 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/04 16:16:24 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "vm.h"
# include "mlx.h"
# define BYTE_PER_COL 64
# define W_LEN 1900
# define W_HGT 1900

typedef struct	s_display
{
	void		*mlx;
	void		*win;
	void		*img;
	t_arena		*arena;
}				t_display;

int		display_all(t_display *dis);
int		mouse_press(int button, int x, int y, t_display *dis);
int		key_press(int keycode, t_display *dis);
int		print_hexa_dis(t_arena *arena, t_display *dis, int index);

#endif
