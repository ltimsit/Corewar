/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/08/31 18:41:01 by ltimsit-         ###   ########.fr       */
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
	int					start;
	int					pc;
	int 				pc_next;
	char				carry;
	int 				nb_live;
	int 				c_done;
	int					c_todo;
	int					c_total;
	int					alive;
	int					dead;
	char				data[4];
	int					param1;
	int					param2;
	int					param3;
	int					dest_pc;

	struct s_process	*next;
}				t_process;

typedef struct	s_champ
{
	int			id;
	char		buff[CHAMP_MAX_SIZE];
	t_process  *process;
	t_process  *p_head;
	header_t	h;
}				t_champ;

typedef struct	s_arena
{
	int				nb_champ;
	int				total_cycle;
	int				actual_cycle;
	int 			nb_check;
	int				nb_live;
	t_champ			champ[MAX_PLAYERS];
	unsigned char 	field[MEM_SIZE];
	t_gc			*gc;
}				t_arena;

typedef struct	s_op
{
	char		*name;
	int			nb_param;
	int			param_type[3];
	uint8_t		opcode;
	int			time;
	char		*description;
	int			ocp;
	int			dir_size;
}				t_op;

typedef struct	s_ocp
{
	uint8_t		ocp;
	int			param1;
	int			param2;
	int			param3;
}				t_ocp;

void	(*g_fct_instr[17])(t_op, t_process *, t_arena *);

/*
** utils.c
*/
void			ft_error(char *message);
int				btohex(unsigned char byte);

/*
** arena.c
*/

void			load_champ(t_arena *arena);
void			print_arena(t_arena *arena);
void 			launch_fight(t_arena *arena);
int				update_pc(int old_pc, int i);

/*
** process.c
*/

void			init_process(t_process *process, int id_champ);
void			add_process(t_arena *arena, int id_champ);
void			print_process(t_champ *champ);

/*
** operation.c
*/

t_ocp			read_ocp(int dir_size, char ocp);
void			read_instruction(t_arena *arena, t_process *process, char opcode);
void			execute_sti(t_process *process, t_arena *field);

#endif
