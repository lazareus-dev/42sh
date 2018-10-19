/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbprintable.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/02 17:35:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/09 20:09:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbprintable(wchar_t *str, int n)
{
	int	bytes;
	int wclen;
	int i;

	i = 0;
	wclen = 0;
	bytes = 0;
	while (str[i])
	{
		wclen = ft_wcbytelen(str[i]);
		if (wclen != -1)
			bytes += wclen;
		if (wclen == -1 && bytes < n)
			return (-1);
		if (bytes > n)
		{
			bytes -= ft_wcbytelen(str[i]);
			break ;
		}
		i++;
	}
	return (bytes);
}
