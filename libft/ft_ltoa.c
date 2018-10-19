/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ltoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 12:39:49 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 11:30:44 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long		ltoa_abs(long n)
{
	return ((n < 0) ? -n : n);
}

static int		ft_nb_len(long n)
{
	int	len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

char			*ft_ltoa(long n)
{
	int		i;
	long	val;
	int		len;
	char	*out;

	len = ft_nb_len(n);
	if (n < 0)
		len++;
	out = (char *)malloc(sizeof(char) * len + 1);
	if (!out)
		return (NULL);
	i = 0;
	val = ltoa_abs(n);
	while (i++ < len)
	{
		out[len - i] = ((val % 10) + '0');
		val /= 10;
	}
	if (n < 0)
		out[0] = '-';
	out[len] = '\0';
	return (out);
}
