/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:33 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 18:22:33 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_wd_cnt(const char *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_wd_len(const char *s, char c)
{
	int len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab_out;

	if (!s || !(tab_out = (char **)malloc(sizeof(char *)
					* (ft_wd_cnt(s, c) + 1))))
		return (NULL);
	tab_out[ft_wd_cnt(s, c)] = NULL;
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (tab_out);
		j = 0;
		if (!(tab_out[i] = (char *)malloc(sizeof(char)
						* (ft_wd_len(s, c) + 1))))
			return (NULL);
		while (*s != c && *s)
			tab_out[i][j++] = *s++;
		tab_out[i++][j] = '\0';
	}
	return (tab_out);
}
