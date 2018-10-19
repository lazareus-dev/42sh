/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_dquote.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 15:28:33 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 12:33:23 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

static char	*backslash_quoting(char *str, int *index)
{
	char *ret;

	ret = NULL;
	if (str[*index + 1] == '\n')
		(*index) += 2;
	else
		ret = get_quoted_char(str, index);
	return (ret);
}

static char	*between_dquotes(char *s, int *i, int *nb_quote)
{
	char *tmp;

	tmp = NULL;
	while (s[*i])
	{
		if (s[*i] == '"')
			(*nb_quote)++;
		else if (s[*i] == '\\')
		{
			tmp = join_and_free(tmp, backslash_quoting(s, i));
			continue;
		}
		tmp = append_char(tmp, s[*i]);
		if (s[*i])
			(*i)++;
		if (*nb_quote == 2)
			break ;
	}
	return (tmp);
}

char		*tokenize_dquote(char *str, int *index)
{
	char	*tmp;
	int		nb_quote;

	nb_quote = 0;
	tmp = between_dquotes(str, index, &nb_quote);
	return (tmp);
}
