/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/28 11:18:40 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"
# include "../../libft/libft.h"



typedef struct	s_process
{
	unsigned char		reg[REG_NUMBER];
	unsigned char		pc;
	int					carry;
	int 				live;
	int					dead;

	struct s_procces	*next;
}				t_process;

typedef struct s_instruc
{
	unsigned char	op;
	unsigned char	ocp;
	int				param_type[3];
	int				param_len[3];
	int				pos;
}				t_instruc;

typedef struct	s_champ
{
	char 		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	int			id;
	int			size;
	int			id_start;
	char		buff[CHAMP_MAX_SIZE];
	t_process  *first_process;
	header_t	h;
	
}				t_champ;

typedef struct	s_arena
{
	t_champ			tchamp[MAX_PLAYERS];
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

void			launch_fight(t_champ *champ);


#endif
