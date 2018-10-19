/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_quoted.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 16:38:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 17:06:30 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	is_backslash_quoted(char *p, int *quoted, int *escaped)
{
	int	ret;

	ret = 0;
	if (*quoted == S_QUOTE)
		ret = 1;
	else if (*quoted == D_QUOTE)
	{
		if (*(p + 1) && ft_strchr(SPCH_BACKSLASH, *(p + 1)))
		{
			ret = 0;
			*escaped = 1;
		}
		else
			ret = 1;
	}
	else if (*escaped)
	{
		ret = 1;
		*escaped = 0;
	}
	else
		*escaped = 1;
	return (ret);
}

static int	is_dquote_quoted(int *quoted, int *escaped)
{
	int ret;

	ret = 0;
	if (*escaped)
	{
		ret = 1;
		*escaped = 0;
	}
	else if (*quoted == S_QUOTE)
		ret = 1;
	else if (*quoted == D_QUOTE)
	{
		ret = 0;
		*quoted = 0;
	}
	else if (!*quoted)
		*quoted = D_QUOTE;
	return (ret);
}

static int	is_squote_quoted(int *quoted, int *escaped)
{
	int ret;

	ret = 0;
	if (*escaped)
	{
		ret = 1;
		*escaped = 0;
	}
	else if (*quoted == D_QUOTE)
		ret = 1;
	else if (*quoted == S_QUOTE)
		*quoted = 0;
	else if (!*quoted)
		*quoted = S_QUOTE;
	return (ret);
}

static int	is_quoted(char *p, int *quoted, int *escaped)
{
	int	ret;

	if (*p == '\\')
		ret = is_backslash_quoted(p, quoted, escaped);
	else if (*p == '\"')
		ret = is_dquote_quoted(quoted, escaped);
	else
		ret = is_squote_quoted(quoted, escaped);
	return (ret);
}

int			ft_is_quoted(char *str, char *ptr)
{
	char	*p;
	int		quoted;
	int		escaped;

	quoted = 0;
	escaped = 0;
	p = str;
	while (*p)
	{
		if (*p == '"' || *p == '\'' || *p == '\\')
		{
			if (p == ptr)
				return (is_quoted(p, &quoted, &escaped));
			else
				p++;
		}
		else
		{
			escaped = 0;
			p++;
		}
	}
	return (0);
}
