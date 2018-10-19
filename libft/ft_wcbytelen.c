/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wcbytelen.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/22 19:57:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/20 14:57:16 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcbytelen(wchar_t c)
{
	size_t	len;

	len = 0;
	if (c < 0x80)
		len += 1;
	else if (c <= 0x7FF)
		len += 2;
	else if (c <= 0xFFFF)
		len += 3;
	else if (c <= 0x10FFFF)
		len += 4;
	return (len);
}
