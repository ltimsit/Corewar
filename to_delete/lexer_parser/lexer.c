#include "lp.h"

char g_sep_tab[10][10] = {
    " ,\t\n#\"", "\"", "\n", " \n\t"
};

int is_valid(char elem, int type)
{
    char *cmp;
    int i;

    i = -1;
    cmp = g_sep_tab[type];
    while (cmp[++i])
        if (elem == cmp[i])
            return (0);
    return (1);
}
int get_type_data(char curr)
{
    if (curr == '"')
        return (T_QUOTE);
    if (curr == '#')
        return (T_COMMENT);
    if (curr == '.')
        return (T_NAME_COM);
    return (0);
}

void add_to_lexer(t_data *data, char *name, int size, int type)
{
    t_elem *new_elem;

    new_elem = malloc(sizeof(t_elem));
    if (!data->lexer->head)
    {
        data->lexer->head = new_elem;
        data->lexer->curr = new_elem;
    }
    else
    {
        data->lexer->curr->next = new_elem;
        data->lexer->curr = new_elem;
    }
    new_elem->name = ft_strdup(name);
    new_elem->size = size;
    new_elem->col_id = data->col_id;
    new_elem->line_id = data->line_id;
    new_elem->next = NULL;
}

int get_new_read(t_data *data)
{
    int ret;

    if (!data->r_data)
    {
        data->r_data = malloc(sizeof(char) * RSIZE + 1);
    }
    ret = read(data->fd, data->r_data, RSIZE);
    data->r_data[ret] = '\0';
    data->r_curr = data->r_data;
    return (ret);
}

int go_to_next(t_data *data)
{
    int i;

    i = -1;
    while ((*data->r_curr || get_new_read(data)) && !is_valid(*data->r_curr, 3))
    {
        if (*data->r_curr == '\n')
        {
            data->line_id++;
            data->col_id = 1;
        }
        else
            data->col_id++;
        data->r_curr++;
    }
    printf("%c\n", *data->r_curr);
    if (!*data->r_curr)
        return (0);
    return (1);
}

int get_elem(t_data *data)
{
    int i;
    char elem[1024];
    int type;

    type = get_type_data(*data->r_curr);
    //elem[0] = *data->r_curr;
    i = 0;
    if (type == T_QUOTE || type == T_COMMENT)
    {
        data->r_curr++;
        data->col_id++;
    }
    if (data->r_curr[i] == ',')
            elem[i++] = data->r_curr[i];
    else
        while (data->r_curr[i] || (get_new_read(data) && (i = 0)))
        {
        //printf("%c\n", data->r_curr[i]);
        if (is_valid(data->r_curr[i], type))
            elem[i++] = data->r_curr[i];
        else
            break;
        }
    elem[i] = '\0';
    if (type == T_QUOTE && *data->r_curr)
    {
        data->r_curr++;
        data->col_id++;
    }

    add_to_lexer(data, elem, i, type);
    sleep(0.5);
    //exit(0);
    data->r_curr += i;
    data->col_id += i;
}

void get_fd(t_data *data, char *av1)
{
    data->fd = open(av1, O_RDONLY);
}

int main(int ac, char **av)
{
    t_data data;
    t_elem *tmp;

    get_fd(&data, av[1]);
    get_new_read(&data);
    data.col_id = 1;
    data.line_id = 1;
    data.lexer = malloc(sizeof(t_lexer));
    data.lexer->head = NULL;
    data.lexer->curr = NULL;
    while (go_to_next(&data))
        get_elem(&data);
    tmp = data.lexer->head;
    while (tmp)
    {
        printf("%s [%d, %d]\n", tmp->name, tmp->line_id, tmp->col_id);
        tmp = tmp->next;
    }
    return (0);
}
