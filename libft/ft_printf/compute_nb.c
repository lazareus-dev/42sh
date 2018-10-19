/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_nb.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/27 18:28:46 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 11:03:01 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	has_prefix(t_spec *spec, int val_len)
{
	if ((spec->indic_hash && ft_strchr("xXb", spec->type) && !spec->iszero)
			|| spec->type == 'p')
		spec->width -= 2;
	else if (spec->indic_hash && ft_strchr("oO", spec->type) &&
			!spec->iszero && (spec->precision <= val_len))
		spec->width -= 1;
	if (spec->indic_hash && ft_strchr("oO", spec->type) &&
			spec->has_prec && spec->precision == 0 && !spec->iszero)
		++spec->precision;
}

int		compute_spec(int val_len, t_spec *spec)
{
	if (spec->precision > val_len)
		spec->precision -= val_len;
	else
		spec->precision = 0;
	if (spec->width)
	{
		spec->width -= spec->precision + val_len;
		if (spec->isneg)
			spec->width -= 1;
	}
	has_prefix(spec, val_len);
	if (spec->indic_plus && !(spec->isneg))
		spec->width--;
	spec->width = (spec->width < 0 ? 0 : spec->width);
	spec->precision = (spec->precision < 0 ? 0 : spec->precision);
	if ((spec->precision < val_len) && spec->has_prec)
		spec->fill_zero = 0;
	return (val_len);
}

int		get_uint_len(uintmax_t val, t_spec *spec)
{
	int		val_len;

	if (ft_strchr("pxX", spec->type))
		val_len = printf_nbrlen_base(val, BASE_XLO);
	else if (ft_strchr("oO", spec->type))
		val_len = printf_nbrlen_base(val, BASE_OCT);
	else if (spec->type == 'b')
		val_len = printf_nbrlen_base(val, BASE_BIN);
	else
		val_len = printf_nbrlen_base(val, BASE_TEN);
	spec->isneg = 0;
	return (val_len);
}
