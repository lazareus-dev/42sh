/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_remove_quoting.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 13:05:49 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/06 13:06:04 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"

static int	is_backslash_quoted(char *p, int *quoted, int *escaped)
{
	int	ret;

	ret = 0;
	if (*quoted == SQUOTE)
		ret = 1;
	else if (*quoted == DQUOTE)
	{
		if (*(p + 1) && ft_strchr(SP_BACKSLASH, *(p + 1)))
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
	else if (*quoted == SQUOTE)
		ret = 1;
	else if (*quoted == DQUOTE)
	{
		ret = 0;
		*quoted = 0;
	}
	else if (!*quoted)
		*quoted = DQUOTE;
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
	else if (*quoted == DQUOTE)
		ret = 1;
	else if (*quoted == SQUOTE)
		*quoted = 0;
	else if (!*quoted)
		*quoted = SQUOTE;
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

int			remove_quoting(char **str)
{
	char	*p;
	int		quoted;
	int		escaped;

	if (!str || !*str)
		return (-1);
	quoted = 0;
	escaped = 0;
	p = *str;
	while (*p)
	{
		if (is_quoting_char(*p))
		{
			if (!is_quoted(p, &quoted, &escaped))
				ft_memmove(p, p + 1, ft_strlen(p));
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
