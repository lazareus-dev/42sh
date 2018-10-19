/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_splitwhitespace.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 13:22:34 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/07 13:28:47 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_wd_cnt(const char *s)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isblank(s[i]))
			i++;
		if (s[i] && !ft_isblank(s[i]))
			count++;
		while (s[i] && !ft_isblank(s[i]))
			i++;
	}
	return (count);
}

static int	ft_wd_len(const char *s)
{
	int len;

	len = 0;
	while (s[len] && !ft_isblank(s[len]))
		len++;
	return (len);
}

char		**ft_splitwhitespace(char const *s)
{
	int		i;
	int		j;
	char	**tab_out;

	if (!s || !(tab_out = (char **)malloc(sizeof(char *)
					* (ft_wd_cnt(s) + 1))))
		return (NULL);
	tab_out[ft_wd_cnt(s)] = NULL;
	i = 0;
	while (*s)
	{
		while (*s && ft_isblank(*s))
			s++;
		if (!*s)
			return (tab_out);
		j = 0;
		if (!(tab_out[i] = (char *)malloc(sizeof(char)
						* (ft_wd_len(s) + 1))))
			return (NULL);
		while (*s && !ft_isblank(*s))
			tab_out[i][j++] = *s++;
		tab_out[i++][j] = '\0';
	}
	return (tab_out);
}
