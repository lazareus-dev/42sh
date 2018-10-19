/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbrbase.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/28 14:40:53 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/29 10:52:27 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrbase(uintmax_t nbr, char *base)
{
	size_t baselen;

	baselen = ft_strlen(base);
	if (nbr >= baselen)
	{
		ft_putnbrbase(nbr / baselen, base);
		ft_putnbrbase(nbr % baselen, base);
	}
	else
		ft_putchar(base[nbr]);
}
