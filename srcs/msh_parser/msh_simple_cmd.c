/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_simple_cmd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 15:50:08 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 15:02:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

/*
**	Fill the char** that will be passed to execve
*/

static void	fill_cmd_tab(t_cmds *node, t_token *tok, int *index)
{
	char	*cmd_arg;

	cmd_arg = NULL;
	if (tok->prev && tok->prev->type == REDIRECTION)
		return ;
	cmd_arg = ft_strdup(tok->token);
	remove_quoting(&cmd_arg);
	node->cmd[(*index)] = cmd_arg;
	(*index)++;
}

static void	build_simple_cmd(t_cmds *cmd)
{
	t_token	*tok;
	int		index;

	index = 0;
	tok = cmd->tokens.first;
	if (cmd->nb_words)
		cmd->cmd = ft_strtab_alloc(cmd->nb_words + 1);
	while (tok)
	{
		if (tok->type == REDIRECTION)
			create_redir(cmd, tok);
		else if (tok->type == WORD && cmd->cmd)
			fill_cmd_tab(cmd, tok, &index);
		tok = tok->next;
	}
	cmd->type = S_CMD;
}

/*
**	Creates new linked list of tokens for a simple command
**	Simple command is only composed of WORD, REDIRECTION
**	and IO_NUMBER
*/

t_cmds		*create_simple_cmd(t_token **tok)
{
	t_cmds	*node;
	t_token	*new_tok;

	node = new_cmds();
	while (*tok && (*tok)->type != OPERATOR)
	{
		if ((*tok)->type == WORD)
			node->nb_words++;
		if ((new_tok = new_token((*tok)->token, (*tok)->type)))
			token_push_back(&node->tokens, new_tok);
		(*tok) = (*tok)->next;
	}
	build_simple_cmd(node);
	return (node);
}
