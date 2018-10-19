/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_exec.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 17:45:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 21:11:59 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_signal.h"

static int	msh_nosuchfile(char *cmd)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int			msh_isdir(char *cmd)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": is a directory", 2);
	return (126);
}

/*
**	Execute cmd
*/

int			exec(char *cmd, char **args, char **tab_env)
{
	if (execve(cmd, args, tab_env) == -1)
		ft_putendl_fd("msh_exec: execve: error", 2);
	exit(1);
	return (0);
}

/*
** Fork and execute cmd
*/

int			fork_and_exec(char *cmd, char **args, char **tab_env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = fork()) < 0)
		fork_error(pid);
	else if (pid == 0)
		exec(cmd, args, tab_env);
	else
		waitpid(pid, &status, 0);
	return (parse_status(status));
}

/*
**	Execute the cmd function with **args agruments
**	int fork decides weather or not we should fork
**	before calling execve
*/

int			msh_exec(char *cmd, char **args, t_shell *shell, int fork)
{
	char	**tabenv;
	int		ret;

	if (access(cmd, F_OK))
		return (msh_nosuchfile(cmd));
	if (ft_is_dir(cmd))
		return (msh_isdir(cmd));
	if (!ft_is_exec(cmd))
		return (msh_notexec(cmd));
	tabenv = lst_to_env(&shell->env);
	if (fork == 1)
		ret = fork_and_exec(cmd, args, tabenv);
	else
		ret = exec(cmd, args, tabenv);
	ft_matricedel(&tabenv);
	return (ret);
}
