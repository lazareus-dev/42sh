/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   argsize.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 11:43:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/23 18:44:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	apply_to_int(t_spec *spec, va_list args)
{
	intmax_t	val;
	size_t		len;

	if (spec->arg_size == ARG_L || spec->type == 'D')
		val = (long)(va_arg(args, long));
	else if (spec->arg_size == ARG_LL)
		val = (long long)(va_arg(args, long long));
	else if (spec->arg_size == ARG_H)
		val = ((short)(va_arg(args, int)));
	else if (spec->arg_size == ARG_HH)
		val = ((char)(va_arg(args, int)));
	else if (spec->arg_size == ARG_J)
		val = ((intmax_t)(va_arg(args, long)));
	else if (spec->arg_size == ARG_Z)
		val = ((size_t)(va_arg(args, long)));
	else
		val = (int)(va_arg(args, int));
	spec->isneg = (val < 0 ? 1 : 0);
	spec->iszero = (val == 0 ? 1 : 0);
	val = (val < 0 ? -val : val);
	len = print_int(&val, spec);
	return (len);
}

size_t	apply_to_uint(t_spec *spec, va_list args)
{
	uintmax_t	val;
	size_t		len;

	if (spec->arg_size == ARG_L || ft_strchr("UO", spec->type))
		val = (unsigned long)(va_arg(args, unsigned long));
	else if (spec->arg_size == ARG_LL)
		val = (unsigned long long)(va_arg(args, unsigned long long));
	else if (spec->arg_size == ARG_H)
		val = ((unsigned short)(va_arg(args, int)));
	else if (spec->arg_size == ARG_HH)
		val = ((unsigned char)(va_arg(args, int)));
	else if (spec->arg_size == ARG_J)
		val = ((uintmax_t)(va_arg(args, uintmax_t)));
	else if (spec->arg_size == ARG_Z)
		val = ((size_t)(va_arg(args, unsigned long)));
	else
		val = (unsigned int)(va_arg(args, unsigned int));
	spec->iszero = (val == 0 ? 1 : 0);
	spec->indic_space = 0;
	spec->indic_plus = 0;
	len = print_uint(&val, spec);
	return (len);
}

size_t	apply_to_char(t_spec *spec, va_list args)
{
	int			val;
	size_t		len;

	len = 0;
	spec->precision = 1;
	if ((spec->arg_size == ARG_L && spec->type == 'c')
			|| spec->type == 'C')
	{
		val = (wchar_t)(va_arg(args, wint_t));
		len = compute_wchar(&val, spec);
	}
	else if ((spec->arg_size == ARG_H && spec->type == 'C')
			|| spec->type == 'c')
	{
		val = ((char)(va_arg(args, int)));
		len = compute_char(val, spec);
	}
	else if ((spec->type != 0) && spec->type == '%')
	{
		val = '%';
		len = compute_char(val, spec);
	}
	return (len);
}

size_t	apply_to_str(t_spec *spec, va_list args)
{
	void		*out;
	size_t		len;

	len = 0;
	if ((spec->arg_size == ARG_L && spec->type == 's')
			|| spec->type == 'S')
	{
		out = (wchar_t *)(va_arg(args, wint_t *));
		if (out == NULL)
			len = compute_ascii("(null)", spec);
		else
			len = compute_wstr(out, spec);
	}
	else if ((spec->arg_size == ARG_H && spec->type == 'S')
			|| spec->type == 's')
	{
		out = (va_arg(args, char *));
		if (out == NULL)
			len = compute_ascii("(null)", spec);
		else
			len = compute_ascii(out, spec);
	}
	return (len);
}

size_t	apply_to_ptr(t_spec *spec, va_list args)
{
	void	*ptr;

	ptr = (va_arg(args, void*));
	spec->iszero = (ptr == NULL ? 1 : 0);
	spec->indic_plus = 0;
	spec->indic_space = 0;
	return (print_uint((uintmax_t *)&ptr, spec));
}
