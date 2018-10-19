/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/09 15:02:45 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/08 15:20:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <wctype.h>
# include <wchar.h>
# include <unistd.h>
# include "../libft.h"

# define BASE_XLO	"0123456789abcdef"
# define BASE_XUP	"0123456789ABCDEF"
# define BASE_TEN	"0123456789"
# define BASE_OCT	"01234567"
# define BASE_BIN	"01"

# define ARG_HH		1
# define ARG_H		2
# define ARG_L		3
# define ARG_LL		4
# define ARG_Z		5
# define ARG_J		6

typedef	struct	s_spec
{
	int			isneg;
	int			iszero;
	int			len;
	char		type;
	char		err;
	char		*indic;
	int			indic_space;
	int			indic_plus;
	int			indic_hash;
	int			align_left;
	int			fill_zero;
	int			width;
	int			has_width;
	int			precision;
	int			has_prec;
	int			arg_size;
}				t_spec;

int				ft_printf(const char *format, ...);

/*
** Specifications getters
*/
int				is_type(char c);
int				is_arg_size(char c);
int				is_indic(char c);
int				is_known(char c);
void			get_arg_size(char *s, t_spec *spec);
void			get_precision(char *s, t_spec *spec, va_list *args);
void			get_indic(char *s, t_spec *spec);
void			get_width(char *s, t_spec *spec, va_list *args);
void			organize_spec(t_spec *spec);

int				parse_args(t_spec *spec, va_list args);

size_t			apply_to_int(t_spec *spec, va_list args);
size_t			apply_to_uint(t_spec *spec, va_list args);
size_t			apply_to_char(t_spec *spec, va_list args);
size_t			apply_to_str(t_spec *spec, va_list args);
size_t			apply_to_ptr(t_spec *spec, va_list args);

int				compute_spec(int val_len, t_spec *spec);
int				get_uint_len(uintmax_t val, t_spec *spec);
size_t			compute_hexa(void *val, t_spec *spec);
int				compute_char(int c, t_spec *spec);
size_t			compute_ascii(void *val, t_spec *spec);
size_t			compute_wchar(wchar_t *val, t_spec *spec);
size_t			compute_wstr(void *val, t_spec *spec);

int				print_int(intmax_t *val, t_spec *spec);
int				print_uint(uintmax_t *val, t_spec *spec);

int				ft_putwchar(wchar_t wc);
int				ft_putwstr(wchar_t *wc);
int				ft_putnwstr(wchar_t *wc, int n);
wchar_t			*ft_putnbytewstr(wchar_t *wc, int n);
int				ft_nbprintable(wchar_t *wc, int n);

#endif
