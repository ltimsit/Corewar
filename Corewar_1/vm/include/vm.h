/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/10 19:21:42 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"
# include "../../libft/libft.h"
# include <ncurses.h>
# include "display.h"

# define PLAYER_1	1
# define PLAYER_2	2
# define PLAYER_3	3
# define PLAYER_4	4
# define CMENU		25
# define AFF_SIZE	128

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
	int					id_champ;
	int					player_nb;
	short				pc;
	char				aff[AFF_SIZE];
	unsigned char		aff_index;
	short 				pc_next;
	char				carry;
	char				opcode;
	int 				nb_live;
	int 				c_done;
	int					c_todo;
	t_param				param;
	struct s_process	*next;
}				t_process;

typedef struct	s_champ
{
	int			id;
	int 		pos;
	char		buff[CHAMP_MAX_SIZE];
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
	int				last_living_champ;
	int				display_on;
	int				total_cycle;
	int				dump_cycle;
	int 			nb_check;
	int				nb_live;
	int				cycle_to_die;
	t_champ			champ[MAX_PLAYERS];
	unsigned char 	field[MEM_SIZE];
	unsigned char 	carriage[MEM_SIZE];
	t_gc			*gc;
	t_op			op[16];
	t_process  		*process;
	t_process 		*p_head;
	t_display		*dis;
	int				pause;
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

int		print_hexa_dis(t_arena *arena, t_display *dis, int index);
int		display_all(t_display *dis);
int		mouse_press(int button, int x, int y, t_display *dis);
int		key_press(int keycode, t_arena *arena);
void	fill_img(char **d_img);
char	*get_data_ptr(void *img_ptr);
int		loop_fight(t_arena *arena);
int		print_nb(t_arena *arena, int nb, int x, int y);
void	init_display(t_arena *arena);
void	print_map(t_arena *arena, int c_nb);

/*
 ** utils.c
 */
void			ft_error(t_arena *arena, char *message);
int				btohex(unsigned char byte);

/*
**tools.c
*/

void			stock_in_param(t_arena *arena, int *param, int size, int pc);
void 			put_param_in_field(t_arena *arena, int param, int size, int pc);
int				fill_index_content(t_arena *arena, t_process *process, int val);
void 			put_data_in_reg(t_process *process, int data,int reg_nb);

/*
**tools2.c
*/

int				check_reg_num(t_param *param, int i);
void			exit_dump(t_arena *arena);

/*
**champ.c
*/

void			print_champ(t_champ *champ);
void			create_add_champ(char *filename, t_arena *arena, int id_champ);

/*
**main.c
*/
unsigned int 	change_endian(unsigned int little);
unsigned char	*open_read(t_arena *arena, char *filename,
	   	unsigned char *buffer);
int				check_argv(t_arena *arena, char **av, int ac);
void			print_usage(t_arena *arena);

/*
 ** arena.c
 */

void			load_champ(t_arena *arena);
void			print_arena(t_arena *arena);
void 			launch_fight(t_arena *arena);
int				update_pc(int old_pc, int i);
void    		process_champ(t_arena *arena);

/*
 ** process.c
 */

void			init_process(t_process *process, int id_champ, int player_nb);
void			add_process(t_arena *arena, int id_champ, int player_nb);
void			print_process(t_process *process);
void    		del_process(t_arena *arena, t_process *todel, t_process *prev);

/*
**op.c
*/
void			set_op_table(t_arena *arena);

/*
 ** operation.c
 */

void			init_fct_exec_tab();
void			init_fct_instr_tab();
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
void			n_print_reg(t_process *process, t_arena *arena, int reg_nb);

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

/*
**or
*/

void			fc_or(t_op op, t_process *process, t_arena *arena);
void			execute_or(t_process *process, t_arena *arena);

/*
**xor
*/

void			fc_xor(t_op op, t_process *process, t_arena *arena);
void			execute_xor(t_process *process, t_arena *arena);

/*
**add
*/

void			fc_add(t_op op, t_process *process, t_arena *arena);
void			execute_add(t_process *process, t_arena *arena);

/*
**sub
*/

void			fc_sub(t_op op, t_process *process, t_arena *arena);
void			execute_sub(t_process *process, t_arena *arena);

/*
**st
*/

void			fc_st(t_op op, t_process *process, t_arena *arena);
void			execute_st(t_process *process, t_arena *arena);
void			fc_sti(t_op op, t_process *process, t_arena *arena);
void			execute_sti(t_process *process, t_arena *arena);

/*
**ld
*/

void			fc_ld(t_op op, t_process *process, t_arena *arena);
void			execute_ld(t_process *process, t_arena *arena);
void			fc_lld(t_op op, t_process *process, t_arena *arena);
void			execute_lld(t_process *process, t_arena *arena);

/*
**ldi
*/

void			fc_ldi(t_op op, t_process *process, t_arena *arena);
void			execute_ldi(t_process *process, t_arena *arena);
void			fc_lldi(t_op op, t_process *process, t_arena *arena);
void			execute_lldi(t_process *process, t_arena *arena);

/*
**fork
*/
void			fc_fork(t_op op, t_process *process, t_arena *arena);
void			execute_fork(t_process *process, t_arena *arena);
void			fc_lfork(t_op op, t_process *process, t_arena *arena);
void			execute_lfork(t_process *process, t_arena *arena);

/*
**aff
*/

void			fc_aff(t_op op, t_process *process, t_arena *arena);
void			execute_aff(t_process *process, t_arena *arena);
#endif
