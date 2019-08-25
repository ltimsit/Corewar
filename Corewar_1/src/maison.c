int get_header(t_data *data)
{
  int		j;
  int		type;

  while (get_to_next_elem(data) && !(D->name_set && D->comment_set))
  {
			if (!(type = name_or_comment(D, D->line + D->curr_index, &j)))
			     return (0);
      D->curr_index = j;
   		if (!(g_fct_tab[type](D, type, j)))
     			return (0);
  }
  return (1);
}

int get_to_next_elem(t_data *data)
{
  while ((!D->line || !D->line[D->curr_index]) || (!D->curr_index = skip_sp(D->line, 0)))
  {
      if (!(D->line = get_line(D)))
          return (0);
      D->curr_line++;
  }
  return (1);
}

int		skip_nosp(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
  if (!line[i])
    return (-1);
	return (i);
}

int get_to_end_elem(t_data *data)
{
  int i;
  char *elem;

  i = 0;
  elem = NULL;
  while ((i = skip_nosp(D->line, D->curr_index)) == -1)
  {
    if (!(elem = ft_add_to_gc(ft_strcpy(D->line + D->curr_index), D->gc)))
      return (0);
    if (!get_line(D))
      return (0);
  }
  if (!elem)
  {
    ft_add_to_gc(ft_strsub(&(D->line + D->curr_index)), D->gc);
  }
  else
  {
    ft_add_to_gc(ft_strsub(&(D->line + D->curr_index)), D->gc); 
  }
  return (i);
}

int		manage_lines(t_data *data)
{
	int		j;
	int		type;

	while (get_to_next_elem(D))
	{
		if (!(type = define_cmd_type(D, D->line + D->curr_index, &j)))
		   return (0);
		D->curr_index = j;
		if (!(g_fct_tab[type](D, type, j)))
			return (0);
	}
	return (1);
}
