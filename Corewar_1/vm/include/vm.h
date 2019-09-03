/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/03 14:37:03 by ltimsit-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"
# include "../../libft/libft.h"
# include <ncurses.h>

# define PLAYER_1 1
# define PLAYER_2 2
# define PLAYER_3 3
# define PLAYER_4 4

typedef struct	s_param
{
	int			value[3];
	int			size[3];
	int 		type[3];
	int			data;
	int			data_size;
	int			dest_pc;
	int			error;
}				t_param;

typedef struct	s_process
{
	int					reg[REG_NUMBER];
	int					start;
	int					pc;
	int 				pc_next;
	char				carry;
	char				opcode;
	int 				nb_live;
	int 				c_done;
	int					c_todo;
	int					c_total;
	int					alive;
	int					dead;
	t_param				param;

	struct s_process	*next;
}				t_process;

typedef struct	s_champ
{
	int			id;
	int 		pos;
	char		buff[CHAMP_MAX_SIZE];
	t_process  *process;
	t_process  *p_head;
	header_t	h;
}				t_champ;

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

typedef struct	s_arena
{
	int				nb_champ;
	int				ncurses;
	int				total_cycle;
	int				actual_cycle;
	int 			nb_check;
	int				nb_live;
	t_champ			champ[MAX_PLAYERS];
	unsigned char 	field[MEM_SIZE];
	t_gc			*gc;
	t_op			op[17];
}				t_arena;


typedef struct	s_ocp
{
	uint8_t		ocp;
	int			param1;
	int			param2;
	int			param3;
}				t_ocp;


void	(*g_fct_instr[17])(t_op, t_process*, t_arena*);
void	(*g_fct_exec[17])(t_process*, t_arena*);

/*
 ** utils.c
 */
void			ft_error(char *message);
int				btohex(unsigned char byte);

/*
**tools.c
*/

void			stock_in_param(t_arena *arena, int *param, int size, int pc);
void 			put_param_in_field(t_arena *arena, int param, int size, int pc);
int				fill_index_content(t_arena *arena, t_process *process, int val);
void 			put_data_in_reg(t_process *process, int reg_nb);

/*
**champ.c
*/

void			print_champ(t_champ *champ);
void			create_add_champ(char *filename, t_arena *arena);

/*
**main.c
*/
unsigned int 	change_endian(unsigned int little);
unsigned char	*open_read(char *filename, unsigned char *buffer);


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
**op.c
*/
void			set_op_table(t_arena *arena);

/*
 ** operation.c
 */

t_param			fill_param(t_arena *arena, t_op op, t_process *process, int elem[3]);
void			fill_elem(t_arena *arena, t_process *process, int nb_elem, int elem[3]);
void			read_ocp(t_param *param, int dir_size, char ocp, int param_type[3]);
void			read_instruction(t_arena *arena, t_process *process, char opcode);
void			execute_sti(t_process *process, t_arena *field);

/*
**ncurses
*/

void			init_ncurses(t_arena *arena);
void 			nprint_arena(t_arena *arena);
int				pc_to_line_col(int pc, int option);
void			n_print_op_exec(int pc, int size, t_arena *arena);
void			n_print_pc(int pc, t_arena *arena, int o);
int				nbtohex(unsigned char byte, int line, int col);


/*
**sti
*/
void			fc_sti(t_op op, t_process *process, t_arena *arena);
void			execute_sti(t_process *process, t_arena *arena);

/*
**live
*/

void			fc_live(t_op op, t_process *process, t_arena *arena);
void			execute_live(t_process *process, t_arena *arena);

/*
**and
*/

void			fc_and(t_op op, t_process *process, t_arena *arena);
void			execute_and(t_process *process, t_arena *arena);

/*
**zjump
*/

void			fc_zjump(t_op op, t_process *process, t_arena *arena);
void			execute_zjump(t_process *process, t_arena *arena);

#endif
