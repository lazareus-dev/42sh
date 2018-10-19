/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_quote.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 15:12:25 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 12:33:21 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

static char	*between_quotes(char *s, int *i, int *nb_quotes)
{
	char		*tmp;

	tmp = NULL;
	while (s[*i])
	{
		if (s[*i] == '\'')
			(*nb_quotes)++;
		tmp = append_char(tmp, s[*i]);
		(*i)++;
		if (*nb_quotes == 2)
			break ;
	}
	return (tmp);
}

char		*tokenize_quote(char *str, int *index)
{
	char	*tmp;
	int		nb_quotes;

	nb_quotes = 0;
	tmp = between_quotes(str, index, &nb_quotes);
	return (tmp);
}
