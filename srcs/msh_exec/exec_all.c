/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_all.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/15 17:34:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 17:34:57 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_exec.h"

int		prerun_cmd(t_cmds *cmd, t_shell *shell)
{
	int	ret;

	save_fd_original_state(shell);
	ret = process_redir(cmd);
	return (ret);
}

int		exec_and_if(t_cmds **cmd, int *ret, t_shell *shell)
{
	if (*ret != 0)
	{
		forward_piped_cmds(cmd);
		return (*ret);
	}
	if ((*cmd)->next && (*cmd)->next->type == PIPE)
		*ret = msh_pipe(cmd, shell);
	else
	{
		msh_expand(*cmd, shell);
		if ((*ret = prerun_cmd((*cmd), shell)))
			return (*ret);
		*ret = dispatch_cmd((*cmd)->cmd, shell, FORK_IT);
		restore_fd_original_state(shell);
		rebuild_fd((*cmd)->redirlst);
	}
	return (*ret);
}

int		exec_or_if(t_cmds **cmd, int *ret, t_shell *shell)
{
	if (*ret == 0)
	{
		forward_piped_cmds(cmd);
		return (*ret);
	}
	if ((*cmd)->next && (*cmd)->next->type == PIPE)
		*ret = msh_pipe(cmd, shell);
	else
	{
		msh_expand(*cmd, shell);
		if ((*ret = prerun_cmd((*cmd), shell)))
			return (*ret);
		*ret = dispatch_cmd((*cmd)->cmd, shell, FORK_IT);
		restore_fd_original_state(shell);
		rebuild_fd((*cmd)->redirlst);
	}
	return (*ret);
}

int		exec_regular(t_cmds *cmd, t_shell *shell)
{
	int	ret;

	msh_expand(cmd, shell);
	if ((ret = prerun_cmd(cmd, shell)))
		return (ret);
	ret = dispatch_cmd(cmd->cmd, shell, FORK_IT);
	restore_fd_original_state(shell);
	rebuild_fd(cmd->redirlst);
	return (ret);
}

void	exec_all(t_cmds *cmds, t_shell *shell)
{
	t_cmds	*node;
	int		ret;

	node = cmds;
	ret = 0;
	while (node && !shell->exit)
	{
		if (node->type == SEPARATOR && node->next)
			ret = 0;
		if (node->type == S_CMD)
		{
			if (node->prev && node->prev->type == AND_IF)
				ret = exec_and_if(&node, &ret, shell);
			else if (node->prev && node->prev->type == OR_IF)
				ret = exec_or_if(&node, &ret, shell);
			else if (node->next && node->next->type == PIPE)
				ret = msh_pipe(&node, shell);
			else
				ret = exec_regular(node, shell);
			node = node->next;
			shell->exit_status = ret;
		}
		else
			node = node->next;
	}
}
