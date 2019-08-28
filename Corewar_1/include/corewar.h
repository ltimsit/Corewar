/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <ltimsit-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:13:52 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/28 11:41:09 by abinois          ###   ########.fr       */
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
	int			jesaispas;
	int			jesaispas2;
}				t_op;

typedef struct	s_data
{
	t_header	header;
	t_gc		*gc;
	t_label		*label;
	int			fd;
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
	read_error
};

char			*err_tab[3];
int				(*g_fct_tab[21])(t_data *, int, int);

/*
** corewar.c    ----------------------------------------------------------------
*/

int				init_data(t_data *data);
void			print_error(t_data *data, char *elem);
int				get_fd_file(char *filename);

/*
** read_lines.c ----------------------------------------------------------------
*/

int				check_in_label_char(char letter);
int				get_type(t_data *data, char *line);

/*
** tools.c      ----------------------------------------------------------------
*/

int				skip_sp(char *line, int i);
int				skip_nosp(char *line, int i);
int				get_error(t_data *data, int err_type, char *elem);
void			fill_op_and_err_tab();


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
int				get_new_read(t_data *data);
int				get_elem(t_data *data, char *tab, int tab_size, char sep_char);
int				go_to_next_elem(t_data *data, int *line_id, int *col_id);
int				read_and_dispatch(t_data *data);

int				btohex(unsigned char byte);

/*
** fc_sti.c     ----------------------------------------------------------------
*/

char			get_param_code(t_data *data, int p1, int p2, int p3);
int				get_registre(t_data *data, char *cmd);
int				get_direct4(t_data *data, char *cmd);
int				fc_sti(t_data *data, int type, int index);
int				fc_and(t_data *data, int type, int index);
int				fc_live(t_data *data, int type, int index);
int				fc_zjmp(t_data *data, int type, int index);
#endif
