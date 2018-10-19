/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:31 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 18:22:31 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char *p;
	char a;

	a = (char)c;
	p = (char *)s;
	while (*p)
	{
		if (*p == a)
			return (p);
		p++;
	}
	if (a == '\0')
		return (p);
	return (NULL);
}
