#include "lp.h"

void parse_list(t_data *data)
{
    t_elem *tmp;

    tmp = data->lexer->head;
    while (tmp->next)
    {
        if (!tmp->type)
        {
            if (*tmp->name == '%')
                tmp->type = check_direct(data, tmp);
            if (*tmp->name == 'r')
                tmp->type = check_registre(data, tmp);
            if (*tmp->name == ',')
                tmp->type = T_SEP;
        }
    }
}

void get_header(t_data *data)
{
    t_elem *tmp;
    char *tofill;
    int name_set;
    int comment_set;

    name_set = 0;
    comment_set = 0;
    tofill = NULL;
    tmp = data->lexer->head;
    while (tmp && !(name_set && comment_set))
    {
        if (tmp->type == T_QUOTE && tofill)
        {
            ft_strcat(tofill, tmp->name);
            tofill = NULL;
        }
        else if (!tofill && !ft_strcmp(tmp->name, NAME_CMD_STRING) && (name_set = 1))
            tofill = data->header.name;
        else if (!tofill && !ft_strcmp(tmp->name, COMMENT_CMD_STRING) && (comment_set = 1))
            tofill = data->header.name;
        else
            get_error(data, tmp);
        tmp = tmp->next;
    }
}

int parser(t_data *data)
{
    data->lexer->curr = data->lexer->head;
    get_header(data);
}
