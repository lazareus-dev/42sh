/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_redir.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 15:48:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 15:48:20 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

void		free_redirlst(t_redir **redir)
{
	t_redir *node;
	t_redir	*hook;

	if (!redir || !*redir)
		return ;
	node = *redir;
	while (node)
	{
		hook = node->next;
		ft_strdel(&node->hdoc.here_doc);
		ft_strdel(&node->hdoc.delimiter);
		ft_strdel(&node->filename);
		free(node);
		node = hook;
	}
}

static void	init_redir(t_redir *redir)
{
	redir->type = 0;
	redir->io_nbr = -1;
	redir->fd = -1;
	redir->filename = NULL;
	redir->hdoc.delimiter = NULL;
	redir->hdoc.here_doc = NULL;
	redir->hdoc.quoted = 0;
	redir->next = NULL;
}

static void	add_redir_node(t_cmds **node, t_redir *redir)
{
	t_redir	*run;

	if (!node || !*node)
		return ;
	if (!(*node)->redirlst)
		(*node)->redirlst = redir;
	else
	{
		run = (*node)->redirlst;
		while (run->next)
			run = run->next;
		run->next = redir;
	}
}

void		remove_redir_nodes(t_cmds *head)
{
	t_token	*tok;
	t_token *hook;

	if (!head)
		return ;
	tok = head->tokens.first;
	while (tok)
	{
		if (tok->type == REDIRECTION)
		{
			if (tok->prev && tok->prev->type == IO_NUMBER)
				del_token(&head->tokens, tok->prev);
			if (tok->next && tok->next->type == WORD)
				del_token(&head->tokens, tok->next);
			hook = tok->next;
			del_token(&head->tokens, tok);
		}
		else
			hook = tok->next;
		tok = hook;
	}
}

/*
**	Creates a redir struct and fills it with the tokens informations
*/

int			create_redir(t_cmds *node, t_token *tok)
{
	t_redir	*redir;

	if (!(redir = (t_redir *)malloc(sizeof(t_redir))))
		return (1);
	init_redir(redir);
	redir->type = tok->optype;
	if (tok->prev && tok->prev->type == IO_NUMBER)
		redir->io_nbr = ft_atoi(tok->prev->token);
	else
	{
		if (redir->type == LESS || redir->type == DLESS
		|| redir->type == DLESSDASH || redir->type == LESSAND)
			redir->io_nbr = STDIN_FILENO;
		else
			redir->io_nbr = STDOUT_FILENO;
	}
	if (redir->type == DLESS || redir->type == DLESSDASH)
		create_here_doc(tok, redir);
	else if (tok->next && tok->next->type == WORD)
		redir->filename = ft_strdup(tok->next->token);
	redir->next = NULL;
	add_redir_node(&node, redir);
	return (0);
}
