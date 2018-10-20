/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_expand_dollar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 17:23:30 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 17:24:05 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_var_utils.h"

static int	dollar_is_quoted(char *dollar, char *token)
{
	int quoted;
	int	escape;
	int	ret;

	quoted = 0;
	escape = 0;
	ret = check_if_quoted(dollar, token, escape, quoted);
	if (ret == DQUOTE)
		ret = 0;
	return (ret);
}

static char	*expand_sp_param(char c)
{
	t_shell	*shell;
	char	*value;

	value = NULL;
	if (!(shell = get_shell()))
		return (NULL);
	if (c == '?')
		value = ft_itoa(shell->exit_status);
	else if (c == '$')
		value = ft_itoa(getpid());
	else if (c == '0')
		value = ft_strdup(shell->process_name);
	else if (c == '!')
		value = ft_itoa(shell->last_process_id);
	return (value);
}

static char	*catch_dollar_value(char **dollar, t_shell *shell)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	while (ft_is_posixname_char((*dollar)[i]))
		i++;
	name = ft_strsub((*dollar), 0, (size_t)i);
	(*dollar) += ft_strlen(name);
	value = msh_getenv(name + 1, shell);
	ft_strdel(&name);
	return (value);
}

static char	*catch_dollar(char **dollar, t_shell *shell)
{
	char	*value;

	if ((*dollar)[1] && ft_strchr(SPECIAL_PARAM, (*dollar)[1]))
	{
		value = expand_sp_param((*dollar)[1]);
		(*dollar) += 2;
	}
	else if (!((*dollar)[1]) || !(ft_is_posixname_char((*dollar)[1])))
	{
		(*dollar) += 1;
		value = ft_strdup("$");
	}
	else
		value = ft_strdup(catch_dollar_value(dollar, shell));
	return (value);
}

int			ft_expand_dollar(char **token, t_shell *shell)
{
	char	*dollar;
	char	*value;
	char	*ptr;
	size_t	hook;

	dollar = *token;
	while ((dollar = ft_strchr(dollar, '$')))
	{
		ptr = dollar;
		if (!dollar_is_quoted(dollar, *token))
			value = catch_dollar(&ptr, shell);
		else
		{
			value = ft_strdup("$");
			ptr++;
		}
		hook = ft_expand_str_part(token, dollar, (ptr - dollar) - 1, value);
		dollar = *token + hook;
		ft_strdel(&value);
	}
	return (0);
}
