/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_nb.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 18:48:13 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 11:08:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_prefix(t_spec *spec)
{
	int len;

	len = 0;
	if (spec->type == 'p')
	{
		ft_putstr("0x");
		return (2);
	}
	if (spec->iszero)
		return (len);
	if (spec->indic_hash && ft_strchr("oO", spec->type) && !spec->has_prec)
		len = ft_putchar('0');
	if (spec->isneg)
		len = ft_putchar('-');
	else if (spec->indic_hash && ft_strchr("xXb", spec->type))
	{
		if (ft_strchr("x", spec->type))
			ft_putstr("0x");
		if (ft_strchr("b", spec->type))
			ft_putstr("0b");
		if (spec->type == 'X')
			ft_putstr("0X");
		return (2);
	}
	return (len);
}

void	preprint(int *len, t_spec *spec)
{
	if (spec->indic_space && !spec->isneg && !spec->indic_plus)
	{
		if (spec->width > 0)
			spec->width--;
		*len += ft_putchar(' ');
	}
	if (spec->width > 0 && !(spec->fill_zero))
		if (!(spec->align_left))
			ft_putnchar(' ', spec->width);
	*len += print_prefix(spec);
	if (spec->indic_plus && !(spec->isneg))
		*len += ft_putchar('+');
	if (spec->width > 0 && spec->fill_zero)
		ft_putnchar('0', spec->width);
	if (spec->precision > 0)
		ft_putnchar('0', spec->precision);
}

void	print_base(uintmax_t *val, t_spec *spec)
{
	if (spec->type == 'x' || spec->type == 'p')
		ft_putnbrbase(*val, BASE_XLO);
	else if (spec->type == 'X')
		ft_putnbrbase(*val, BASE_XUP);
	else if (spec->type == 'o' || spec->type == 'O')
		ft_putnbrbase(*val, BASE_OCT);
	else if (spec->type == 'b')
		ft_putnbrbase(*val, BASE_BIN);
	else
		ft_putnbrbase(*val, BASE_TEN);
}

int		print_uint(uintmax_t *val, t_spec *spec)
{
	int len;
	int print;

	print = 1;
	len = get_uint_len(*val, spec);
	if (spec->iszero && spec->has_prec && !spec->precision)
	{
		len = 0;
		print = 0;
	}
	compute_spec(len, spec);
	preprint(&len, spec);
	if (print)
		print_base(val, spec);
	if (spec->align_left)
		ft_putnchar(' ', spec->width);
	if (spec->indic_hash && ft_strchr("oO", spec->type) && !print &&
			spec->has_prec && spec->precision == 0 && spec->iszero)
		len += ft_putchar('0');
	return (spec->width + spec->precision + len);
}

int		print_int(intmax_t *val, t_spec *spec)
{
	int len;
	int print;

	print = 1;
	len = ft_nbr_len(*val);
	if (spec->iszero && spec->has_prec && !spec->precision)
	{
		len = 0;
		print = 0;
	}
	compute_spec(len, spec);
	preprint(&len, spec);
	if (print)
		ft_putllnbr(*val);
	if (spec->align_left)
		ft_putnchar(' ', spec->width);
	return (spec->width + spec->precision + len);
}
