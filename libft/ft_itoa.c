/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:26 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 11:29:54 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long		itoa_abs(int n)
{
	return ((n < 0) ? (long)-n : (long)n);
}

static int		ft_nb_len(int n)
{
	int	len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	int		i;
	long	val;
	int		len;
	char	*out;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nb_len(n);
	if (n < 0)
		len++;
	out = (char *)malloc(sizeof(char) * len + 1);
	if (!out)
		return (NULL);
	i = 0;
	val = itoa_abs(n);
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
