/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 18:24:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 16:47:30 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"

int		is_quoting_char(char c)
{
	if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else if (c == '\\')
		return (BACKSLASH);
	else
		return (UNQUOTED);
}

int		get_token_type(char *token, char delimiter)
{
	if (!token)
		return (0);
	if (is_redirection(token))
		return (REDIRECTION);
	else if (is_operator(token))
		return (OPERATOR);
	else if (ft_str_is_numeric(token)
		&& (delimiter == '<' || delimiter == '>'))
		return (IO_NUMBER);
	else if (ft_strequ("\n", token))
		return (NEWLINE);
	else
		return (WORD);
}

void	skip_whitespaces(char *str, int *index)
{
	while (is_separator(str[*index]))
		(*index)++;
}
