/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/29 19:06:38 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"
# include "../../libft/libft.h"



typedef struct	s_process
{
	int					reg[REG_NUMBER];
	int					pc;
	char				carry;
	int 				nb_live;
	int					alive;
	int					dead;

	struct s_procces	*next;
}				t_process;

typedef struct	s_champ
{
	int			id;
	char		buff[CHAMP_MAX_SIZE];
	t_process  *first_process;
	header_t	h;	
}				t_champ;

typedef struct	s_arena
{
	int				total_cycle;
	int				actual_cycle;
	int 			nb_check;
	int				nb_live;
	t_champ			champ[MAX_PLAYERS];
	unsigned char 	field[MEM_SIZE];

}				t_arena;

/*
** utils.c
*/
void			ft_error(char *message);
int				btohex(unsigned char byte);

/*
** arena.c
*/

void			print_arena(t_arena *arena);
void 			launch_fight(t_arena *arena);

#endif
