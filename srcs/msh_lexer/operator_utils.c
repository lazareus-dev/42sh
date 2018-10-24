/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 18:24:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:58:25 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_redirection(char *token)
{
	if (ft_strequ(token, "<"))
		return (LESS);
	else if (ft_strequ(token, ">"))
		return (GREAT);
	else if (ft_strequ(token, "<<"))
		return (DLESS);
	else if (ft_strequ(token, ">>"))
		return (DGREAT);
	else if (ft_strequ(token, "<&"))
		return (LESSAND);
	else if (ft_strequ(token, ">&"))
		return (GREATAND);
	else if (ft_strequ(token, "<>"))
		return (LESSGREAT);
	else if (ft_strequ(token, "<<-"))
		return (DLESSDASH);
	else
		return (NO_OP);
}

int		is_operator(char *token)
{
	if (ft_strequ(token, "|"))
		return (PIPE);
	else if (ft_strequ(token, ";"))
		return (SEPARATOR);
	if (ft_strequ(token, "&&"))
		return (AND_IF);
	else if (ft_strequ(token, "||"))
		return (OR_IF);
	return (NO_OP);
}

int		is_operator_char(char c)
{
	return (
			c == '<'
			|| c == '>'
			|| c == '|'
			|| c == ';'
			|| c == '&');
}

int		is_operator_ctrl_char(char c)
{
	return (
			c == '|'
			|| c == ';'
			|| c == '&');
}

int		get_operator_type(char *token, int toktype)
{
	int	optype;

	if (toktype == REDIRECTION)
		optype = is_redirection(token);
	else if (toktype == OPERATOR)
		optype = is_operator(token);
	else
		optype = NO_OP;
	return (optype);
}
