/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_dispatch_cmd.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:47:09 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:46:05 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_var_utils.h"

#include <dirent.h>

char		*iterate_path(char *cmd, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*full_path;

	full_path = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dirent->d_name, cmd) == 0)
		{
			full_path = ft_triplejoin(path, "/", cmd);
			break ;
		}
	}
	closedir(dir);
	return (full_path);
}

char		*get_cmd_path(char *cmd, t_shell *shell)
{
	char			**paths;
	char			*full_path;
	char			*path_env;
	int				i;

	full_path = NULL;
	path_env = msh_getenv("PATH", shell);
	paths = ft_strsplit(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		if (paths[i][0] == '~')
			paths[i] = expand_tilde_regular(paths[i], shell);
		if ((full_path = iterate_path(cmd, paths[i++])))
			break ;
	}
	ft_matricedel(&paths);
	if (full_path)
		msh_addbin_to_table(cmd, full_path);
	return (full_path);
}

int			empty_path_env(t_shell *shell)
{
	char	*path;

	path = msh_getenv("PATH", shell);
	if (!path)
		return (1);
	return (0);
}

static char	*get_hashbin_path(char *cmd, t_hash_table *bintable)
{
	char			*full_path;
	t_list			*node;

	full_path = NULL;
	if (!bintable)
		return (NULL);
	if (!(node = ft_hash_getbin(bintable, cmd)))
		return (NULL);
	full_path = ft_strdup((char *)node->content);
	return (full_path);
}

int			dispatch_cmd(char **av, t_shell *shell, int fork)
{
	char	*cmd_path;
	int		ret;

	if (!av || av[0] == NULL)
		return (1);
	cmd_path = NULL;
	if (is_valid_assignment(*av))
		ret = msh_local_var(av, shell);
	else if (ft_strchr(av[0], '/'))
		ret = msh_exec(av[0], av, shell, fork);
	else if (is_builtin(av))
		ret = msh_builtin(av, shell);
	else if ((cmd_path = get_hashbin_path(av[0], shell->bin_table)) != NULL)
		ret = msh_exec(cmd_path, av, shell, fork);
	else if ((cmd_path = get_cmd_path(av[0], shell)) != NULL)
		ret = msh_exec(cmd_path, av, shell, fork);
	else if (ft_is_binary(av[0]) && empty_path_env(shell))
		ret = msh_exec(av[0], av, shell, fork);
	else
		ret = cmd_error(av[0]);
	ft_strdel(&cmd_path);
	return (shell->exit_status = ret);
}
