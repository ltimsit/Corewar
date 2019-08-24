/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:13:52 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/08/24 18:21:27 by ltimsit-         ###   ########.fr       */
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
	t_gc		*gc;
	int			fd;
	int			err;
	char		*line;
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
	syntax
};

char			*err_tab[2];
int				(*g_fct_tab[21])(t_data *, int, int);

/*
** corewar.c    ----------------------------------------------------------------
*/

int				init_data(t_data *data);
void			print_error(t_data *data);
int				get_fd_file(char *filename);

/*
** read_lines.c ----------------------------------------------------------------
*/

char			*get_line(t_data *data);
int				check_in_label_char(char letter);
int				name_or_comment(t_data *data, char *line, int *end_index);
int				define_cmd_type(t_data *data, char *line, int *end_index);
int				manage_lines(t_data *data);

/*
** tools.c      ----------------------------------------------------------------
*/

int				skip_sp(char *line, int i);
int				skip_nosp(char *line, int i);
int				get_error(t_data *data, int err_type);
void			fill_op_and_err_tab();

/*
** champtools.c ----------------------------------------------------------------
*/

char			*stock_namecom(char *line);
int				fc_comment(t_data *data, int type, int j);
int				fc_name(t_data *data, int type, int j);
int				mem_stock(t_data *data, char *content, int content_size);
#endif
