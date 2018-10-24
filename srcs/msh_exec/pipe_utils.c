/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 10:04:08 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 10:04:09 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_parser.h"

#include <errno.h>

int		pipe_error(void)
{
	ft_putstr_fd("lsh: pipe error: ", 2);
	if (errno == ENFILE)
		ft_putendl_fd("Too many opened files", 2);
	else if (errno == EMFILE)
		ft_putendl_fd("Too many used fds", 2);
	return (1);
}

void	delete_pipe_nodes(t_cmds **cmds)
{
	t_cmds *node;
	t_cmds *hook;

	node = *cmds;
	while (node && (node->type == PIPE || node->type == S_CMD))
	{
		hook = node->next;
		if (node->type == PIPE)
			detach_cmds_node(node);
		node = hook;
	}
}

void	forward_piped_cmds(t_cmds **cmds)
{
	while (*cmds)
	{
		if ((*cmds)->type == S_CMD)
		{
			if ((*cmds)->next && (*cmds)->next->type == PIPE)
				(*cmds) = (*cmds)->next->next;
			else
				break ;
		}
		else
			break ;
	}
}
