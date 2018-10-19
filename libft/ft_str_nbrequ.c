/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_nbrequ.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 17:33:11 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 17:33:19 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_nbrequ(char *ref, char *test)
{
	size_t len;

	len = 0;
	while (ref[len] && test[len] && (ref[len] == test[len]))
		len++;
	return (len);
}
