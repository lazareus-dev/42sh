/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbr_len_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/28 16:41:06 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/28 16:46:07 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbr_len_base(uintmax_t nbr, int base)
{
	size_t	len;

	len = 1;
	while (nbr /= base)
		len++;
	return (len);
}
