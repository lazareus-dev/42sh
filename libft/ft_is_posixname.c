/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_posixname.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/30 13:57:56 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 14:06:46 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_posixname(char *name)
{
	size_t i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (0);
	while (name[i])
	{
		if (!ft_is_posixname_char(name[i]))
			return (0);
		++i;
	}
	return (1);
}
