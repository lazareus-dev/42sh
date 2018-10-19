/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmds.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/09 19:25:52 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:59:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

void	detach_cmds_node(t_cmds *del)
{
	t_tokenlst	*tokenlst;
	t_cmds		*prev;
	t_cmds		*next;

	if (!del)
		return ;
	if ((prev = del->prev))
		prev->next = del->next;
	if ((next = del->next))
		next->prev = del->prev;
	ft_matricedel(&del->cmd);
	free_redirlst(&del->redirlst);
	tokenlst = &(del->tokens);
	free_tokenlst(&tokenlst, 1);
	free(del);
}

int		init_cmds(t_cmds *ast)
{
	ast->nb_words = 0;
	ast->tokens.first = NULL;
	ast->tokens.last = NULL;
	ast->tokens.nb_token = 0;
	ast->redirlst = NULL;
	ast->cmd = NULL;
	ast->prev = NULL;
	ast->next = NULL;
	return (0);
}

t_cmds	*new_cmds(void)
{
	t_cmds	*node;

	if (!(node = (t_cmds *)malloc(sizeof(t_cmds))))
		return (NULL);
	init_cmds(node);
	return (node);
}

void	push_back_cmds(t_cmds **head, t_cmds *node)
{
	t_cmds	*run;

	if (!head)
		return ;
	if (!(*head))
		*head = node;
	else
	{
		run = (*head);
		while (run->next)
			run = run->next;
		run->next = node;
		node->prev = run;
	}
}

void	free_cmds(t_cmds **head)
{
	t_cmds		*cmds;
	t_tokenlst	*tokenlst;

	if (!head || !*head)
		return ;
	cmds = *head;
	ft_matricedel(&cmds->cmd);
	free_redirlst(&cmds->redirlst);
	tokenlst = &(cmds->tokens);
	free_tokenlst(&tokenlst, 1);
	if (cmds->next)
		free_cmds(&cmds->next);
	free(*head);
	*head = NULL;
}
