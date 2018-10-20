/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_environment.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vischlum <vischlum@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 17:55:22 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 18:13:33 by vischlum    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_setunsetenv.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_lstenv.h"

void	init_shlvl(t_shell *shell)
{
	char	*tmp_lvl;
	char	*shlvl;
	int		lvl;

	if (!getenv("SHLVL"))
		lvl = 0;
	else
		lvl = ft_atoi(getenv("SHLVL"));
	lvl += 1;
	tmp_lvl = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", tmp_lvl);
	msh_setenv(shlvl, shell);
	ft_strdel(&shlvl);
	ft_strdel(&tmp_lvl);
}

/*
** Creates some default environment variables in case
** an empty environment has been passed to the Lazyshell
*/

void	init_default_var(t_shell *shell)
{
	char	*pwd;
	char	*path;
	char	*getpwd;

	getpwd = get_pwd();
	pwd = ft_strjoin("PWD=", getpwd);
	path = ft_super_realloc(ft_strdup("PATH="), get_envpath_from_file());
	msh_setenv(pwd, shell);
	if (!getenv("PATH"))
		msh_setenv(path, shell);
	init_shlvl(shell);
	msh_setenv("CLICOLOR=1", shell);
	ft_strdel(&getpwd);
	ft_strdel(&pwd);
	ft_strdel(&path);
}

/*
** Build the linked-list version of the environ char**
*/

void	init_environ(t_shell *shell)
{
	extern char **environ;
	t_var		*elem;
	int			i;

	shell->env.first = NULL;
	i = 0;
	if (environ && environ[0])
	{
		while (environ[i])
		{
			elem = new_env(environ[i]);
			elem->exported = 1;
			push_back(&(shell->env), elem);
			++i;
		}
	}
	init_default_var(shell);
}
