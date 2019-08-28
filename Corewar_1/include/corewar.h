/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <ltimsit-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:13:52 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 17:28:23 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <stdint.h>
# include "libft.h"
# include "op.h"
# include <stdbool.h>
# include "ft_printf.h"

# define D data
# define MEMSIZE 2048
# define READSIZE 20
# define PARAM_SIZE 128

typedef struct	s_param
{
	int		para[3];
	int		val[3];
	char	ocp;
	char	cmd[PARAM_SIZE];
}				t_param;

typedef struct	s_label_add
{
	char				*name;
	int					pc;
	struct s_label_add	*next;
}				t_label_add;

typedef struct	s_label_instr
{
	char					*name;
	int						mem_index;
	struct s_label_instr	*next;
}				t_label_instr;

typedef struct	s_label
{
	t_label_add			*lst_add;
	t_label_add			*head_add;
	t_label_instr		*lst_instr;
	t_label_instr		*head_instr;
}				t_label;

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

typedef struct	s_data
{
	t_header	header;
	t_gc		*gc;
	t_label		*label;
	int			fd;
	int			pc;
	int			err;
	char		*line;
	char		*start;
	int			curr_line;
	int			curr_index;
	char		*chmp_name;
	char		*chmp_com;
	bool		name_set;
	bool		comment_set;
	char		*mem_stock;
	int			mem_stock_index;
	int			mem_size;
}				t_data;

enum			e_op
{
	live,
	ld,
	st,
	add,
	sub,
	cand,
	cor,
	cxor,
	zjmp,
	ldi,
	sti,
	cfork,
	lld,
	lldi,
	lfork,
	aff,
	zero
};

enum			e_cmd
{
	name_line = 1,
	comment_line,
	label_line,
	command_line
};

enum			e_error
{
	lexical,
	syntax,
	read_error,
	param,
	coma
};

char			*err_tab[5];

/*
** corewar.c    ----------------------------------------------------------------
*/

int				init_data(t_data *data);
void			print_error(t_data *data, char *elem);
int				get_fd_file(char *filename);

/*
** read_lines.c ----------------------------------------------------------------
*/


/*
** tools.c      ----------------------------------------------------------------
*/

int				skip_sp(char *line, int i);
int				skip_nosp(char *line, int i);
int				get_error(t_data *data, int err_type, char *elem);
void			fill_op_and_err_tab();
int				get_new_read(t_data *data);


/*
** champtools.c ----------------------------------------------------------------
*/

int				fc_namecom(t_data *data, char *namecom, int size);
int				mem_stock(t_data *data, char *content, int content_size);
int				change_endian(t_data *data, unsigned int h);

/*
** header.c     ----------------------------------------------------------------
*/

int				set_header(t_data *data);
int				get_elem(t_data *data, char *tab, int tab_size, char sep_char);
int				go_to_next_elem(t_data *data, int *line_id, int *col_id);
int				get_type(t_data *data, char *line);
int				read_and_dispatch(t_data *data);

/*
** byte_to_hexa.c---------------------------------------------------------------
*/

int				btohex(unsigned char byte);

/*
** param.c      ----------------------------------------------------------------
*/

char			get_param_code(t_data *data, int p1, int p2, int p3);
int				get_registre(t_data *data, char *cmd);
int				get_direct4(t_data *data, char *cmd);
int				fc_cmd(t_data *data, int type, t_op op);

/*
** param_rools.c----------------------------------------------------------------
*/

int				check_separator_char(t_data *data);
void			init_param_tab(int *params);
int				check_param(t_data *data, int type, int cmd_param, char *cmd);
int				param_type_tool(t_data *data, char *cmd, int *val);
int				get_param_type(t_data *data, char *cmd, int *val);

/*
** label.c      ----------------------------------------------------------------
*/

int				check_in_label_char(char letter);
int				add_to_label_instr(t_data *data, char *elem, int mem_index);
int				add_to_label_list(t_data *data, char *elem, int pc);
int				calc_val_from_pc(int curr_pc, int label_pc);
int				check_label(t_data *data, char *elem);

#endif
