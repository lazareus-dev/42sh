/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_match.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/02 13:51:21 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 13:52:31 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	if (*s1 == '\0' && *s2 == '*')
		return (match(s1, s2 + 1));
	if ((*s1 == '\0' && *s2 != '*'))
		return (0);
	if (*s1 == *s2 && *s2 != '*')
		return (match(s1 + 1, s2 + 1));
	if (*s2 == '*')
		return (match(s1 + 1, s2) || match(s1, s2 + 1));
	return (0);
}

int	ft_match(char *s1, char *s2)
{
	char	*comp;
	int		ret;

	if (s2)
		comp = ft_strjoin(s2, "*");
	else
		comp = ft_strdup("*");
	ret = match(s1, comp);
	ft_strdel(&comp);
	return (ret);
}
