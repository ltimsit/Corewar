/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:24:14 by abinois           #+#    #+#             */
/*   Updated: 2019/09/16 11:55:08 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# define BUFF_SIZE_GNL 1024
# define ULL	unsigned long long

typedef struct	s_gcl
{
	void			*ptr;
	struct s_gcl	*next;
}				t_gcl;

typedef struct	s_gc
{
	t_gcl			*list;
	t_gcl			*head;
	int				size;
}				t_gc;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
int				ft_memdel(void **ap, int return_value);
void			ft_bzero(void *s, size_t n);

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnchr(const char *s, int c, size_t len);
char			*ft_strstr(const char *str, const char *tofind);
char			*ft_strnstr(const char *str, const char *tofind, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_str_is_digit(char *s);

int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);

void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putnstr(const char *s, size_t n);
void			ft_putstrclr(const char *s, const char *color_input);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);
void			ft_display_file(char *filename);

char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_str_up(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strsub(const char **s, unsigned int strt, size_t ln, int o);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strjoinfr(char **s1, char **s2, char option);
char			*ft_strtrim(const char *s);
char			*ft_strnrev(char *str, size_t len);
char			**ft_strsplit(const char *s, char c);
char			*ft_str_add(char **s1, char **s2, char option);

t_list			*ft_lstnew(const void *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t			ft_lst_size(t_list *alst);
t_list			**ft_lst_rev(t_list **alst);

int				ft_po(int nb, int po);
int				ft_sqrt(int nb);
int				ft_sqrtup(int nb);
int				ft_abs(int n);
void			ft_swap(int	*a, int *b);
void			ft_chen(char *octet, int size);

int				ft_get_next_line(const int fd, char **line, int o);
int				ft_skip_char(char *line, char c, int i);
int				ft_skip_nochar(char *line, char c, int i);

char			*ft_itoa(int nbr);
char			*ft_llutoa(unsigned long long nbr);
char			*ft_lltoa(long long nbr);
char			*ft_octatoa(unsigned long long nbr);
char			*ft_hexatoa(unsigned long long nbr);
char			*ft_bitoa(void *input, size_t size);

void			*ft_free_stropt(char **s1, char **s2, char option);
void			*ft_alloc_gc(int size, int size_type, t_gc *gc);
int				ft_free_gc(t_gc *gc);
int				ft_add_to_gc(void *ptr, t_gc *gc);

void			ft_fili(const char *file, size_t line);

#endif
