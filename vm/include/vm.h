/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avanhers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:13:50 by avanhers          #+#    #+#             */
/*   Updated: 2019/09/17 15:21:21 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"
# include "../../libft/libft.h"
# include "display.h"

# define PLAYER_1	1
# define PLAYER_2	2
# define PLAYER_3	3
# define PLAYER_4	4
# define CMENU		25
# define AFF_SIZE	128

#====== define A			arena
# define PRO		process

typedef struct	s_param======
{
	int			value[3];
	int			size[3];
	int			type[3];
	int			data;
	int			data_size;
	int			dest_pc;
	int			error;
}========================				t_param;

typedef struct	s_process
{=================
	int					reg[REG_NUMBER];
	int					id_champ;
	int					player_nb;
	short				pc;
	char				aff[AFF_SIZE];
	unsigned char		aff_index;
	short				pc_next;
	char				carry;
	char				opcode;
	int					nb_live;
	int					c_done;
	int					c_todo;
	t_param				param;
	struct s_process	*next;
}				t_process;

typedef struct	s_champ
{
	int			id;
	int			pos;
	int			nb_live;
	char		buff[CHAMP_MAX_SIZE];
	t_header	h;
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
	int				curr_cycle;
	int				dump_cycle;
	int				nb_check;
	int				nb_live;
	int				cycle_to_die;
	t_champ			champ[MAX_PLAYERS];
	unsigned char	field[MEM_SIZE];
	unsigned char	carriage[MEM_SIZE];
	t_gc			*gc;
	t_op			op[16];
	t_process		*process;
	t_process		*p_head;
	int				nb_process;
	t_display		*dis;
	int				cycle_before_dis;
	int				pause;
	int				finish;
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
**end_of_fight  ----------------------------------------------------------------
*/
void			aff_winner(t_arena *arena, int color, char *name);
void			print_winner_dis(t_arena *arena, int i);
void			print_winner(t_arena *arena);

/*
**exit_fcts 	 ---------------------------------------------------------------
*/
void			exit_dis(t_arena *arena);
void			free_l_process(t_arena *arena);
void			exit_fight(t_arena *arena);

/*
**init_display  ----------------------------------------------------------------
*/
void			print_map(t_arena *arena, int c_nb);
int				print_hexa_dis(t_arena *arena, t_display *dis, int index);
void			init_display(t_arena *arena);

/*
**display_tools ----------------------------------------------------------------
*/
void			fill_color_value(unsigned char *carriage, int size, int p_nb);
void			clear_carriage_superpo(t_arena *arena);
void			print_reg_dis(t_arena *arena, t_process *process);
int				print_reg_click(t_arena *arena, int x, int y);
int				print_nb(t_arena *arena, int nb, int x, int y);

/*
**display_tools2----------------------------------------------------------------
*/
int				print_nb_dec(t_arena *arena, int nb, int x, int y);
void			fill_img(char **d_img);
void			fill_border(t_arena *arena);
void			print_champ_live(t_arena *arena);
void			print_process_dis(t_arena *arena);

/*
**hook			----------------------------------------------------------------
*/
char			*get_data_ptr(void *img_ptr);
void			speed_tool(t_arena *arena, char option);
int				key_press(int keycode, t_arena *arena);
int				mouse_press(int button, int x, int y, t_arena *arena);
int				loop_fight(t_arena *arena);

/*
**tools			----------------------------------------------------------------
*/
unsigned int	chen4(unsigned int little);
void			stock_in_param(t_arena *arena, int *param, int size, int pc);
void			put_param_in_field(t_arena *ar, t_process *process, int size);
int				fill_index_content(t_arena *arena, t_process *process, int val);
void			put_data_in_reg(t_process *process, int data, int reg_nb);

/*
**tools2		----------------------------------------------------------------
*/
int				check_reg_num(t_param *param, int i);
void			exit_dump(t_arena *arena);
void			ft_error(t_arena *arena, char *message);
int				update_pc(int old_pc, int i);
void			print_usage(t_arena *arena);

/*
**champ			----------------------------------------------------------------
*/
void			print_champ(t_champ *champ);
t_champ			new_champ(t_arena *arena, unsigned char *buf);
void			create_add_champ(char *filename, t_arena *arena, int id_champ);
void			sort_champ(t_arena *arena);
void			load_champ(t_arena *arena);

/*
**main			----------------------------------------------------------------
*/
unsigned char	*open_read(t_arena *arena, char *file, unsigned char *buf);
int				get_arg(int i, char **av, int ac, int *argument);
void			check_argv(t_arena *arena, char **av, int ac);
void			init_corewar(t_arena *arena);

/*
**arena			----------------------------------------------------------------
*/
void			print_arena(t_arena *arena);
void			manage_pc_carriage(t_arena *ar, t_process *process, int new_pc);
void			execution(t_arena *arena, t_process *process);
void			check_process(t_arena *arena, t_process *process);
void			launch_fight(t_arena *arena);

/*
**process		----------------------------------------------------------------
*/
void			process_process(t_arena *arena);
int				verif_process(t_arena *arena, t_process *head);
void			init_process(t_process *process, int id_champ, int player_nb);
void			add_process(t_arena *arena, int id_champ, int player_nb);
void			del_process(t_arena *arena, t_process *todel, t_process *prev);

/*
**fill_tab		----------------------------------------------------------------
*/
void			set_op_table(t_arena *arena);
void			init_fct_exec_tab();
void			init_fct_instr_tab();

/*
**operation		----------------------------------------------------------------
*/
t_param			fill_param(t_arena *arena, t_op op, t_process *process,
		int elem[3]);
int				is_valid_type(int param_type, int cmp);
int				is_integer(char *str);
int				check_id(t_arena *arena, char *str);
void			read_ocp(t_param *param, int dir_size, char ocp, t_op op);

/*
**live_aff		----------------------------------------------------------------
*/
int				check_valid_champ(int id, t_arena *arena);
void			fc_live(t_op op, t_process *process, t_arena *arena);
void			execute_live(t_process *process, t_arena *arena);
void			fc_aff(t_op op, t_process *process, t_arena *arena);
void			execute_aff(t_process *process, t_arena *arena);

/*
**and_zjump		----------------------------------------------------------------
*/
void			fc_zjump(t_op op, t_process *process, t_arena *arena);
void			execute_zjump(t_process *process, t_arena *arena);
void			fc_and(t_op op, t_process *process, t_arena *arena);
void			execute_and(t_process *process, t_arena *arena);

/*
**orxor			----------------------------------------------------------------
*/
void			fc_or(t_op op, t_process *process, t_arena *arena);
void			execute_or(t_process *process, t_arena *arena);
void			fc_xor(t_op op, t_process *process, t_arena *arena);
void			execute_xor(t_process *process, t_arena *arena);

/*
**addsub		----------------------------------------------------------------
*/
void			fc_add(t_op op, t_process *process, t_arena *arena);
void			execute_add(t_process *process, t_arena *arena);
void			fc_sub(t_op op, t_process *process, t_arena *arena);
void			execute_sub(t_process *process, t_arena *arena);

/*
**st			----------------------------------------------------------------
*/
void			fc_st(t_op op, t_process *process, t_arena *arena);
void			execute_st(t_process *process, t_arena *arena);
void			fc_sti(t_op op, t_process *process, t_arena *arena);
void			execute_sti(t_process *process, t_arena *arena);

/*
**ld			----------------------------------------------------------------
*/
void			fc_ld(t_op op, t_process *process, t_arena *arena);
void			execute_ld(t_process *process, t_arena *arena);
void			fc_lld(t_op op, t_process *process, t_arena *arena);
void			execute_lld(t_process *process, t_arena *arena);

/*
**ldi			----------------------------------------------------------------
*/
void			fc_ldi(t_op op, t_process *process, t_arena *arena);
void			execute_ldi(t_process *process, t_arena *arena);
void			fc_lldi(t_op op, t_process *process, t_arena *arena);
void			execute_lldi(t_process *process, t_arena *arena);

/*
**fork			----------------------------------------------------------------
*/
void			fc_fork(t_op op, t_process *process, t_arena *arena);
void			execute_fork(t_process *process, t_arena *arena);
void			fc_lfork(t_op op, t_process *process, t_arena *arena);
void			execute_lfork(t_process *process, t_arena *arena);

#endif
