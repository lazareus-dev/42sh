/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_args.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:16:31 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/04 14:44:57 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_args(t_spec *spec, va_list args)
{
	int		len;

	len = 0;
	if (spec->err != '\0')
		len = compute_char(spec->err, spec);
	else if (ft_strchr("idD", spec->type))
		len = apply_to_int(spec, args);
	else if (ft_strchr("bouxXUO", spec->type))
		len = apply_to_uint(spec, args);
	else if (spec->type == 'c' || spec->type == 'C')
		len = apply_to_char(spec, args);
	else if (spec->type == 's' || spec->type == 'S')
		len = apply_to_str(spec, args);
	else if (spec->type == 'p')
		len = apply_to_ptr(spec, args);
	else if (spec->type == '%')
		len = apply_to_char(spec, args);
	return (len);
}
