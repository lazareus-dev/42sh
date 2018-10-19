/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_normal.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 15:21:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 15:22:31 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

char			*tokenize_regular(char *s, int *i)
{
	char		*ret;

	ret = NULL;
	while (s[*i] && !is_separator(s[*i]) && !is_operator_char(s[*i]))
	{
		if (s[*i] == '\'')
			ret = join_and_free(ret, tokenize_quote(s, i));
		else if (s[*i] == '"')
			ret = join_and_free(ret, tokenize_dquote(s, i));
		else if (s[*i] == '\\')
			ret = join_and_free(ret, tokenize_backslash(s, i));
		else
		{
			ret = append_char(ret, s[*i]);
			(*i)++;
		}
	}
	return (ret);
}
