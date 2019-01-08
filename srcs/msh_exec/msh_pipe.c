/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_pipes.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 15:10:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 13:15:17 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"

#include <unistd.h>
#include <sys/resource.h>

static void	forward_pipes(t_cmds **cmds)
{
	while (*cmds && (*cmds)->type == S_CMD && (*cmds)->next)
		(*cmds) = (*cmds)->next;
}

static int	pipe_cmd(t_cmds *cmd, t_pipe p, t_shell *shell)
{
	int ret;

	if (p.input != STDIN_FILENO)
		dup2(p.input, STDIN_FILENO);
	else
		dup2(p.first, STDIN_FILENO);
	if (cmd->next && cmd->next->type == S_CMD && p.output == STDOUT_FILENO)
		dup2(p.fds[WRITE_END], STDOUT_FILENO);
	msh_expand(cmd, shell);
	if ((ret = process_redir(cmd)))
		return (ret);
	close(p.fds[READ_END]);
	ret = dispatch_cmd(cmd->cmd, shell, 0);
	if (is_builtin(cmd->cmd))
	{
		free_tokenlst(&shell->tokenlst, 0);
		free_cmds(&shell->cmds);
		ft_exit_shell();
	}
	exit(ret);
}

static int	pipeline(t_cmds *cmds, t_shell *shell)
{
	t_pipe	p;
	pid_t	pid;
	int		status;

	status = 0;
	p.first = STDIN_FILENO;
	while (cmds && cmds->type == S_CMD)
	{
		p.input = STDIN_FILENO;
		p.output = STDOUT_FILENO;
		if (pipe(p.fds) < 0)
			return (pipe_error());
		if ((pid = fork()) < 0)
			return (fork_error());
		if (pid == CHILD)
			pipe_cmd(cmds, p, shell);
		manage_pipe_fds(&p);
		cmds = cmds->next;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (parse_status(status));
}

int			check_nb_pipes(t_cmds *cmd)
{
	t_cmds			*node;
	struct rlimit	lim;
	int				i;

	getrlimit(RLIMIT_NPROC, &lim);
	i = 0;
	node = cmd;
	while (node && i < INT32_MAX)
	{
		i++;
		node = node->next;
	}
	if ((unsigned long long)i > lim.rlim_cur)
	{
		ft_putendl_fd("lsh : Too many processes in the pipeline", 2);
		return (1);
	}
	return (0);
}

int			msh_pipe(t_cmds **cmds, t_shell *shell)
{
	int		ret;

	save_fd_original_state(shell);
	delete_pipe_nodes(cmds);
	if (!check_nb_pipes(*cmds))
		ret = pipeline((*cmds), shell);
	else
		ret = 1;
	forward_pipes(cmds);
	restore_fd_original_state(shell);
	return (ret);
}
