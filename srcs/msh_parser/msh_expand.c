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
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

int			check_if_quoted(char *dollar, char *token, int *escape, int *quoted)
{
	int		i;
	int		ret;
	char	c;

	i = 0;
	while ((c = token[i]) && (token + i) != dollar)
	{
		if (c == '\\' && *quoted != SQUOTE/* && quoted != DQUOTE*/)
			*escape = !*escape;
		else if ((c == '\"' || c == '\'') && !*escape)
		{
			if (*quoted && *quoted == is_quoting_char(c))
				*quoted = UNQUOTED;
			else if (!*quoted)
				*quoted = is_quoting_char(c);
		}
		if (c != '\\' && *quoted != SQUOTE)
			*escape = 0;
		i++;
	}
	ret = *quoted ? *quoted : *escape;
	return (ret);
}

static int	is_escaped(char *needle, char *token)
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

static void	expand_tilde_dollar_cmd(char **word, t_shell *shell)
{
	char	*tilde;

	if ((tilde = ft_strchr(*word, '~')) && !is_escaped(tilde, *word))
		*word = expand_tilde_regular(*word, shell);
	if (*word && ft_strchr(*word, '$'))
		ft_expand_dollar(word, shell);
}

void		msh_expand(t_cmds *cmds, t_shell *shell)
{
	int i;

	i = 0;
	while (cmds->cmd[i])
	{
		expand_tilde_dollar_cmd(&cmds->cmd[i], shell);
		remove_quoting(&cmds->cmd[i]);
		i++;
	}
}
