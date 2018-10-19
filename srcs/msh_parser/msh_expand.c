/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_expand.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 11:17:20 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 15:01:18 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_parser.h"

int			is_escaped(char *needle, char *token)
{
	int		escaped;

	escaped = 0;
	while (*token || token == needle)
	{
		if (*token == '\\')
			escaped = 1;
		if ((*token == '\\') && ((token + 1) == needle))
			break ;
		token++;
	}
	return (escaped);
}

void		expand_tilde_dollar(t_token *token, t_shell *shell)
{
	char	*tilde;

	if (token->type == WORD)
		if ((tilde = ft_strchr(token->token, '~'))
				&& !is_escaped(tilde, token->token))
			token->token = expand_tilde_regular(token->token, shell);
	if (token->token && ft_strchr(token->token, '$'))
		ft_expand_dollar(&(token->token), shell);
}

void		msh_expand(t_tokenlst *tokenlst, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokenlst->first;
	while (tmp)
	{
		if (!tmp->token)
		{
			tmp = tmp->next;
			continue ;
		}
		expand_tilde_dollar(tmp, shell);
		tmp = tmp->next;
	}
}
