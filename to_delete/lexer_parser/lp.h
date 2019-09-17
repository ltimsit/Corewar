#include "libft.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define COMMENT_SEP "\n"
#define QUOTE_SEP "\""
#define PARAM_SEP " \t\n,"
#define CMD_SEP " \t\n"
#define NEXT_SEP " \t\n,#"
#define T_QUOTE 1
#define T_COMMENT 2
#define T_NEXT 3
#define RSIZE 1000

typedef struct  s_elem
{
    char        *name;
    int         size;
    int         col_id;
    int         line_id;
    struct s_elem *next;
}               t_elem;

typedef struct  s_lexer
{
    t_elem      *head;
    t_elem      *curr;
}               t_lexer;

typedef struct  s_data
{
    int         fd;
    char        *r_data;
    char        *r_curr;
    int         col_id;
    int         line_id;
    t_lexer     *lexer;
    t_header    header;
}               t_data;
