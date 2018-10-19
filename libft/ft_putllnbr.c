/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putllnbr.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:29 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/29 13:08:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	ft_putllnbr(intmax_t n)
{
	if (n == INT64_MIN)
	{
		ft_putchar('9');
		ft_putllnbr(223372036854775808);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = -n;
		}
		if (n < 10)
		{
			ft_putchar(n + '0');
		}
		if (n > 9)
		{
			ft_putllnbr(n / 10);
			ft_putchar(n % 10 + '0');
		}
	}
}
