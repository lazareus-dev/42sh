/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_env_dispatch.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 12:27:35 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 15:10:04 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_var_utils.h"

int			dispatch_env(char **av, t_shell *shell, int fork)
{
	char	*cmd_path;
	int		ret;

	if (!av || av[0] == NULL)
		return (1);
	cmd_path = NULL;
	if (ft_strchr(av[0], '/'))
		ret = msh_exec(av[0], av, shell, fork);
	else if (is_valid_assignment(*av))
		ret = msh_local_var(av, shell);
	else if (is_builtin(av))
		ret = msh_builtin(av, shell);
	else if ((cmd_path = get_cmd_path(av[0], shell)) != NULL)
		ret = msh_exec(cmd_path, av, shell, fork);
	else if (ft_is_binary(av[0]) && empty_path_env(shell))
		ret = msh_exec(av[0], av, shell, fork);
	else
		ret = cmd_error(av[0]);
	ft_strdel(&cmd_path);
	return (shell->exit_status = ret);
}
