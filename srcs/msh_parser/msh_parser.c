/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 10:46:06 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 15:03:02 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

static t_cmds	*create_operator(t_token *tok)
{
	t_cmds	*node;
	t_token	*new_tok;

	node = new_cmds();
	if ((new_tok = new_token(tok->token, tok->type)))
		token_push_back(&node->tokens, new_tok);
	node->type = node->tokens.first->optype;
	return (node);
}

/*
**	Checks for syntax errors
**	Creates the simple commands and the redirections
*/

t_cmds			*msh_parser(t_tokenlst *tokenlst, t_shell *shell)
{
	t_cmds	*cmds;
	t_token	*tok;

	(void)shell;
	if (check_syntax(tokenlst))
		return (NULL);
	del_token(tokenlst, tokenlst->last);
	tok = tokenlst->first;
	cmds = NULL;
	while (tok)
	{
		if (tok->type != OPERATOR)
			push_back_cmds(&cmds, create_simple_cmd(&tok));
		if (tok && tok->type == OPERATOR)
			push_back_cmds(&cmds, create_operator(tok));
		if (tok)
			tok = tok->next;
	}
	return (cmds);
}
