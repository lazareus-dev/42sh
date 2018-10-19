/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putunichar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 22:54:58 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/09 20:09:25 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

int		ft_put4bytes(wchar_t c)
{
	int bytes;

	bytes = ft_putchar((c >> 18) + 0xF0);
	bytes += ft_putchar(((c >> 12) & 0x3F) + 0x80);
	bytes += ft_putchar(((c >> 6) & 0x3F) + 0x80);
	bytes += ft_putchar((c & 0x3F) + 0x80);
	return (bytes);
}

int		ft_put3bytes(wchar_t c)
{
	int bytes;

	bytes = ft_putchar((c >> 12) + 0xE0);
	bytes += ft_putchar(((c >> 6) & 0x3F) + 0x80);
	bytes += ft_putchar((c & 0x3F) + 0x80);
	return (bytes);
}

int		ft_put2bytes(wchar_t c)
{
	int bytes;

	bytes = ft_putchar((c >> 6) + 0xC0);
	bytes += ft_putchar((c & 0x3F) + 0x80);
	return (bytes);
}

int		ft_putwchar(wchar_t c)
{
	int bytes;

	bytes = 0;
	if (c < 0 || c > 0x10FFFF || ((c >= 0xD800) && (c <= 0xDFFF)))
		return (-1);
	if (c <= 127)
		bytes += ft_putchar(c);
	else if (c <= 255 && MB_CUR_MAX == 1)
		bytes += ft_putchar((char)c);
	else if (c > 127 && MB_CUR_MAX > 1)
	{
		if (c < 0x800)
			bytes += ft_put2bytes(c);
		else if (c < 0x10000)
			bytes += ft_put3bytes(c);
		else if (c < 0x110000)
			bytes += ft_put4bytes(c);
	}
	else
		bytes = -1;
	return (bytes);
}
