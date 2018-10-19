/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_spec.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 11:38:59 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/08 18:48:19 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_arg_size(char *s, t_spec *spec)
{
	int i;

	i = 0;
	while (i <= spec->len)
	{
		if (is_arg_size(s[i]))
		{
			if (s[i] == 'h' && spec->arg_size < ARG_H)
				spec->arg_size = ARG_H;
			if ((s[i + 1] == 'h' || s[i - 1] == 'h'))
				spec->arg_size = ARG_HH;
			if (s[i] == 'l' && spec->arg_size < ARG_L)
				spec->arg_size = ARG_L;
			if ((s[i + 1] == 'l' || s[i - 1] == 'l') &&
							spec->arg_size < ARG_LL)
				spec->arg_size = ARG_LL;
			if (s[i] == 'z' && spec->arg_size < ARG_Z)
				spec->arg_size = ARG_Z;
			if (s[i] == 'j' && spec->arg_size < ARG_J)
				spec->arg_size = ARG_J;
		}
		++i;
	}
}

void	get_precision(char *s, t_spec *spec, va_list *args)
{
	int i;
	int prec;

	i = 0;
	while (++i < spec->len)
	{
		if (s[i + 1] && s[i] == '.')
		{
			spec->has_prec = 1;
			if (s[i + 1] == '*')
			{
				if ((prec = va_arg(*args, int)) >= 0)
					spec->precision = prec;
				else
					spec->has_prec = 0;
			}
			else if (ft_isdigit(s[i + 1]))
				spec->precision = ft_abs_int(ft_atoi(s + i + 1));
			else
				spec->precision = 0;
		}
	}
}

void	get_indic(char *s, t_spec *spec)
{
	int i;
	int stop;

	stop = 0;
	i = 1;
	while (i < spec->len)
	{
		if (s[i] == ' ')
			spec->indic_space = 1;
		if (s[i] == '#')
			spec->indic_hash = 1;
		if (s[i] == '+')
			spec->indic_plus = 1;
		if (s[i] == '-')
			spec->align_left = 1;
		if (s[i] == '.')
			stop = 1;
		if (s[i] == '0' && !ft_isdigit(s[i - 1]) && !stop)
			spec->fill_zero = 1;
		i++;
	}
}

void	get_width(char *s, t_spec *spec, va_list *args)
{
	int i;

	i = 0;
	while (i < spec->len && s[i] != '.')
	{
		if (ft_isdigit(s[i]) || s[i] == '*')
		{
			if (s[i] == '*')
				spec->width = va_arg(*args, int);
			else
			{
				spec->width = ft_atoi(s + i);
				while (ft_isdigit(s[i]))
					++i;
				--i;
			}
			if (spec->width < 0)
				spec->align_left = 1;
			spec->width = ft_abs_int(spec->width);
			spec->has_width = 1;
		}
		i++;
	}
}

void	organize_spec(t_spec *spec)
{
	if (spec->align_left || (spec->precision &&
				ft_strchr("dDuUioOxXb", spec->type)))
		spec->fill_zero = 0;
}
