/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_builtin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 21:15:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:59:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_setunsetenv.h"

#include <unistd.h>

int		is_builtin(char **av)
{
	if (!av || !(*av))
		return (0);
	return (ft_strequ(av[0], "exit")
			|| ft_strequ(av[0], "cd")
			|| ft_strequ(av[0], "echo")
			|| ft_strequ(av[0], "setenv")
			|| ft_strequ(av[0], "unsetenv")
			|| ft_strequ(av[0], "env")
			|| ft_strequ(av[0], "hash")
			|| ft_strequ(av[0], "history")
			|| ft_strequ(av[0], "export")
			|| ft_strequ(av[0], "unset"));
}

/*
** Launch the right builtin
*/

int		msh_builtin(char **av, t_shell *shell)
{
	int ret;

	ret = 0;
	if (ft_strequ(av[0], "echo"))
		ret = msh_echo(++av);
	else if (ft_strequ(av[0], "cd"))
		ret = msh_cd(++av, shell);
	else if (ft_strequ(av[0], "env"))
		ret = msh_env(++av, shell);
	else if (ft_strequ(av[0], "setenv"))
		ret = msh_setenv(av[1], shell);
	else if (ft_strequ(av[0], "unsetenv"))
		ret = msh_unsetenv(++av, shell);
	else if (ft_strequ(av[0], "exit"))
		ret = msh_exit(++av, shell);
	else if (ft_strequ(av[0], "hash"))
		ret = msh_hash(++av, shell);
	else if (ft_strequ(av[0], "history"))
		ret = msh_history(++av, shell);
	else if (ft_strequ(av[0], "export"))
		ret = msh_export(++av, shell);
	else if (ft_strequ(av[0], "unset"))
		ret = msh_unset(++av, shell);
	return (ret);
}
