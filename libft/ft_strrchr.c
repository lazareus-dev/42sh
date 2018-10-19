/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:33 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 18:22:33 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	get_nextc(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char		*ft_strrchr(const char *s, int c)
{
	char *ret;

	ret = (char *)s;
	while (*ret)
	{
		if (*ret == c)
			if (!(get_nextc(ret + 1, c)))
				return (ret);
		ret++;
	}
	if (!c)
		return (ret);
	return (NULL);
}
