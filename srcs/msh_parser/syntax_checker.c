/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   syntax_checker.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 14:22:00 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 14:22:02 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_lexer.h"

static int	syntax_error(t_token *tok, int type)
{
	ft_putstr_fd("lsh: syntax error", 2);
	if (type == 1)
	{
		ft_putendl_fd(": unexpected end of file", 2);
		return (1);
	}
	ft_putstr_fd(" near unexpected token ", 2);
	ft_putchar_fd('`', 2);
	if (type == OPERATOR)
		ft_putstr_fd(tok->token, 2);
	else if (type == REDIRECTION && tok->next)
		ft_putstr_reveal_blanks(tok->next->token);
	ft_putendl_fd("\'", 2);
	return (1);
}

static int	check_operator(t_token *tok)
{
	if (tok->prev == NULL)
		return (OPERATOR);
	if (tok->prev && tok->prev->type != WORD)
		return (OPERATOR);
	if (!tok->next || tok->next->type == NEWLINE)
		return (1);
	return (0);
}

static int	check_redir(t_token *tok)
{
	if (!(tok->next) || (tok->next->type != WORD))
		return (REDIRECTION);
	return (0);
}

static int	check_unexpected_eof(char *str)
{
	t_input	input;
	int		ret;

	init_input(&input);
	input.line = ft_strjoin(str, "\n");
	ret = check_line_integrity(&input);
	ft_strdel(&input.line);
	if (ret)
		return (1);
	return (0);
}

/*
**	Seeks for syntax errors
*/

int			check_syntax(t_tokenlst *head)
{
	t_token *tok;
	int		ret;

	tok = head->first;
	ret = 0;
	while (tok && !ret)
	{
		if (tok->type == WORD)
			ret = check_unexpected_eof(tok->token);
		else if (tok->type == REDIRECTION)
			ret = check_redir(tok);
		else if (tok->type == OPERATOR)
			ret = check_operator(tok);
		if (ret)
			break ;
		tok = tok->next;
	}
	ret ? syntax_error(tok, ret) : 0;
	return (ret);
}
