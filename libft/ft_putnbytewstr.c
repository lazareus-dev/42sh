/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbytewstr.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/02 16:14:56 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/09 20:05:40 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_putnbytewstr(wchar_t *str, int n)
{
	wchar_t	*out;
	int		bytes;
	int		wclen;
	int		i;

	out = (wchar_t *)ft_memalloc(sizeof(wchar_t) * (n + 1));
	i = 0;
	bytes = 0;
	while (str[i])
	{
		if ((wclen = ft_wcbytelen(str[i])) >= 0)
		{
			bytes += wclen;
			if (bytes <= n)
				out[i] = str[i];
			else
				return (out);
		}
		else
			return (out);
		i++;
	}
	return (out);
}
