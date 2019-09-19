/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:23:19 by abinois           #+#    #+#             */
/*   Updated: 2019/06/10 14:21:44 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <string.h>
# include <stdint.h>

# define F		flagz
# define I		infloat
# define LD 	long double
# define VL		va_list
# define UI		unsigned int
# define ULL	unsigned long long

typedef struct	s_float
{
	bool		sign;
	int			expo;
	char		*mantissa;
	char		*deci_str;
	char		*fracti_str;
	char		*zersp;
	char		*res;
}				t_float;

typedef struct	s_flag
{
	bool		zer;
	bool		minus;
	bool		sp;
	bool		plus;
	bool		hash;
	size_t		field;
	bool		dot;
	size_t		preci;
	bool		l;
	bool		ll;
	bool		bigl;
	bool		h;
	bool		hh;
	bool		b;
	char		conv;
	long long	nb;
	ULL			nbou;
}				t_flag;

int				g_fd;

int				ft_printf(const char *fmt, ...);
char			*m_to_buf(int *m, char *buf, const char *fmt, int i);
char			*arg_to_buf(char **buf, char **arg);
int				print_return(va_list ap, char **buf);

char			*reput_backzer(char **str);
void			fill_colors(char **color);
int				what_color(char *buf, int i);
int				return_value(char *buf);
int				put_color(char *buf, int x, int i);

char			*p_sign(t_flag *flagz, char *res, size_t *i);
char			*p_toa(char *toa, char *res, size_t *c, t_flag flagz);
char			*p_zer(size_t flag, char *res, size_t *c, size_t l_nb);
char			*put_hash(char *res, size_t *c, t_flag flagz, size_t l_nb);
char			*put_sp(t_flag flagz, size_t *c, size_t lmax, char *res);

void			check_first_flagz(const char *fmt, t_flag *flagz, int *i);
void			check_l_flagz(const char *fmt, t_flag *flagz, int *i);
void			check_bh_flagz(const char *fmt, t_flag *flagz, int *i);
void			check_f_p(const char *fmt, t_flag *flagz, int *i, va_list ap);
char			*check_all(const char *fmt, t_flag *flagz, int *i, VL ap);

char			*check_conv1(const char *fmt, t_flag flagz, int *i, VL ap);
char			*check_conv2(const char *fmt, t_flag flagz, int *i, VL ap);
char			*check_conv3(const char *fmt, t_flag flagz, int *i, VL ap);
void			reset_flagz(t_flag *flagz);

char			*over_63(t_float *infloat, char **res, int x, int i);
char			*deci_float(t_float *infloat, LD nb);
char			*fracti_float(t_float *infloat, int i);
int				fracti_algo(char **buffer, char **res, int *x);
int				preci_float(char **fracti, char **deci, t_flag flagz, int i);

char			*str_times_two(char **str, char ret, int i);
char			*str_by_two(char **str, char ret, int i);
char			*get_mantissa(LD dbl, int i, size_t size);
int16_t			get_exponent(LD dbl, t_float **infloat);
int				preci_banks(char **deci, char **fracti, int i);

char			*p_sign_float(char **str, t_flag flagz, t_float *infloat);
int				get_zersp(t_float *infloat, t_flag flagz);
t_float			*reset_float(t_float *infloat);
char			*free_float(t_float **infloat);
char			*inf_or_nan(t_float *infloat, t_flag flagz, char *sp, size_t l);

char			*get_f_start(t_float **infloat, LD *nb, VL ap, t_flag flagz);
char			*get_f_min(t_float *infloat, t_flag flagz);
char			*get_f_zer(t_float *infloat, t_flag flagz);
char			*get_f_else(t_float *infloat, t_flag flagz);
char			*get_float(t_flag flagz, VL ap);

char			*malloc_str_c(t_flag flagz, VL ap, char option, char x);
char			*malloc_str_s(t_flag flagz, VL ap);
char			*malloc_str_xp(t_flag flagz, VL ap);
char			*malloc_str_ou(t_flag flagz, VL ap);
char			*malloc_str_d(t_flag flagz, VL ap);

char			*fill_str_d(t_flag flagz, size_t lmax, char **toa, char *res);
char			*fill_str_ou(t_flag flagz, size_t lmax, char **toa, char *res);
char			*fill_str_xp(t_flag flagz, size_t lmax, char **toa, char *res);
char			*fill_str_s(t_flag flagz, size_t lmax, char *toa, char *res);
char			*fill_nomin_xp(t_flag flagz, size_t l_nb, char *res, size_t *c);

long long		check_d_i_flagz(t_flag flagz, VL ap);
ULL				check_poux_flagz(t_flag flagz, VL ap);
LD				check_f_flagz(t_flag flagz, VL ap);

#endif
