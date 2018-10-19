/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute_str.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/27 18:26:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 18:00:01 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		compute_char(int c, t_spec *spec)
{
	int		len;
	char	f;

	f = (spec->fill_zero ? '0' : ' ');
	len = 0;
	if (spec->width < 1)
		spec->width = 1;
	if (spec->align_left)
		len += ft_putchar(c);
	len += ft_putnchar(f, (spec->width - 1));
	if (!spec->align_left)
		len += ft_putchar(c);
	return (len);
}

size_t	compute_ascii(void *val, t_spec *spec)
{
	char	f;
	size_t	val_len;
	char	*buffer;

	f = (spec->fill_zero ? '0' : ' ');
	val_len = ft_strlen((char *)val);
	if (spec->precision == 0 && !spec->has_prec)
		spec->precision = val_len;
	buffer = ft_strndup(((char *)val), spec->precision);
	if (spec->width < (int)ft_strlen(buffer))
		spec->width = ft_strlen(buffer);
	val_len = ft_strlen(buffer);
	if (spec->align_left)
		write(1, buffer, ft_strlen(buffer));
	val_len += ft_putnchar(f, (spec->width - ft_strlen(buffer)));
	if (!spec->align_left)
		write(1, buffer, ft_strlen(buffer));
	free(buffer);
	return (val_len);
}

int		check_wstr_valid(void *val, t_spec *spec)
{
	int val_len;

	val_len = ft_wsbytelen(val);
	if (!spec->has_prec)
	{
		if (val_len == -1)
			return (-1);
		else
			spec->precision = val_len;
	}
	val_len = ft_nbprintable(val, spec->precision);
	return (val_len);
}

size_t	compute_wstr(void *val, t_spec *spec)
{
	char	f;
	int		val_len;
	wchar_t	*out;

	f = (spec->fill_zero ? '0' : ' ');
	val_len = check_wstr_valid(val, spec);
	if (val_len == -1)
		return (-1);
	spec->width = spec->width < val_len ? val_len : spec->width;
	out = ft_putnbytewstr(val, spec->precision);
	if (spec->align_left)
		ft_putwstr(out);
	val_len = ft_putnchar(f, (spec->width - val_len));
	if (!spec->align_left)
		ft_putwstr(out);
	val_len += ft_wsbytelen(out);
	return (val_len);
}

size_t	compute_wchar(wchar_t *val, t_spec *spec)
{
	int		val_len;
	wchar_t c;

	c = *val;
	if ((val_len = ft_wcbytelen(c)) < 0)
		return (-1);
	if (spec->precision == 0)
		spec->precision = val_len;
	if (spec->width < val_len)
		spec->width = val_len;
	if (spec->align_left)
		ft_putwchar(c);
	val_len += ft_putnchar(' ', (spec->width - val_len));
	if (!spec->align_left)
		ft_putwchar(c);
	return (val_len);
}
