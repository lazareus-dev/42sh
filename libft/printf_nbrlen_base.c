/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printf_nbrlen_base.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/28 17:15:21 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/29 17:28:59 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	printf_nbrlen_base(uintmax_t nbr, char *base)
{
	int		len;
	size_t	baselen;

	len = 0;
	baselen = ft_strlen(base);
	if (nbr >= baselen)
	{
		len += printf_nbrlen_base(nbr / baselen, base);
		len += printf_nbrlen_base(nbr % baselen, base);
	}
	else
		return (1);
	return (len);
}
