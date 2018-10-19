/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_parse.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 15:41:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 15:41:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

char		*join_and_free(char *s1, char *s2)
{
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	free(s1);
	free(s2);
	return (ret);
}

char		*append_char(char *str, char c)
{
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	if (!str)
	{
		tmp = (char *)ft_memalloc(2);
		tmp[i] = c;
	}
	else
	{
		if (c == '\0')
			return (str);
		len = ft_strlen(str) + 1;
		tmp = (char *)ft_memalloc(len + 1);
		ft_strcpy(tmp, str);
		while (str[i])
			i++;
		tmp[i] = c;
		ft_strdel(&str);
	}
	return (tmp);
}

int			is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
