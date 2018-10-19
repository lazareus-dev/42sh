/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_expand_str_part.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/02 15:16:05 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:49:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*triple_join(char *s1, char *s2, char *s3)
{
	char	*merged;

	merged = NULL;
	if (s1)
		merged = ft_strdup(s1);
	if (s2)
		merged = ft_str_joinordup(merged, s2);
	if (s3)
		merged = ft_str_joinordup(merged, s3);
	return (merged);
}

size_t		ft_expand_str_part(char **str, char *ptr, size_t size,
		char *replace)
{
	size_t	len_start;
	size_t	ret;
	char	*start;
	char	*end;

	start = ft_strsub((*str), 0, (ptr - (*str)));
	len_start = ft_strlen(start);
	end = ft_strsub((*str), (len_start + size + 1),
			(ft_strlen(*str) - (len_start + size)));
	ft_strdel(str);
	(*str) = triple_join(start, replace, end);
	ret = ft_strlen(start) + ft_strlen(replace);
	ft_strdel(&start);
	ft_strdel(&end);
	return (ret);
}
