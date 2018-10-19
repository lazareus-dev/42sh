/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_getenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 11:44:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/31 18:12:30 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

char	*findenv(const char *name, char **environ, int *len)
{
	int			i;
	char		**p;
	char		*cp;
	const char	*np;

	np = name;
	while (*np && *np != '=')
		++np;
	*len = np - name;
	p = environ;
	while ((cp = *p) != NULL)
	{
		np = name;
		i = *len;
		while (i && *cp)
		{
			if (*cp++ != *np++)
				break ;
			i--;
		}
		if (i == 0 && *cp++ == '=')
			return (cp);
		++p;
	}
	return (NULL);
}

char	*ft_getenv(const char *name, char **environ)
{
	int			len;

	if (!name || !environ)
		return (NULL);
	len = 0;
	return (findenv(name, environ, &len));
}
