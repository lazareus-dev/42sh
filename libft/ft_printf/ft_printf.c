/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maintests.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:16:14 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:05:39 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	init(t_spec *spec)
{
	spec->isneg = 0;
	spec->len = 1;
	spec->type = 0;
	spec->indic = NULL;
	spec->indic_space = 0;
	spec->indic_plus = 0;
	spec->indic_hash = 0;
	spec->align_left = 0;
	spec->width = 0;
	spec->has_width = 0;
	spec->fill_zero = 0;
	spec->precision = 0;
	spec->has_prec = 0;
	spec->arg_size = 0;
	spec->err = '\0';
}

t_spec	get_spec(const char *s, va_list *args)
{
	t_spec	spec;
	int		i;

	i = 1;
	init(&spec);
	while (s[i] && (is_known(s[i])))
		i++;
	if (!s[i])
	{
		spec.len = i;
		return (spec);
	}
	if (!is_type(s[i]))
		spec.err = s[i];
	else
		spec.type = s[i];
	spec.len = i + 1;
	get_arg_size((char *)s, &spec);
	get_indic((char *)s, &spec);
	get_width((char *)s, &spec, args);
	get_precision((char *)s, &spec, args);
	organize_spec(&spec);
	return (spec);
}

int		print_all(const char **format, va_list *args, int *len)
{
	int		tmp;
	t_spec	spec;

	while (**format)
	{
		if (**format == '%')
		{
			spec = get_spec(*format, args);
			if (is_type(spec.type) || spec.err)
			{
				if ((tmp = parse_args(&spec, *args)) != -1)
					*len += tmp;
				else
					return (-1);
			}
			*format += spec.len;
		}
		else
		{
			*len += ft_putchar(**format);
			*format += 1;
		}
	}
	return (*len);
}

int		ft_printf(const char *format, ...)
{
	va_list args;
	int		len;

	len = 0;
	if (ft_strchr(format, '%') == 0)
	{
		ft_putstr(format);
		return (ft_strlen(format));
	}
	va_start(args, format);
	if (print_all(&format, &args, &len) == -1)
		return (-1);
	va_end(args);
	return (len);
}
