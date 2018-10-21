/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_error.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 22:18:25 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/21 12:53:27 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/msh_error.h"

void	*msh_cdenverror(int issue)
{
	if (issue == HOME_NOT_SET)
		ft_putendl_fd("cd: HOME not set", 2);
	else if (issue == OLDPWD_NOT_SET)
		ft_putendl_fd("cd: OLDPWD not set", 2);
	else if (issue == USAGE)
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	return (NULL);
}

int		msh_notdir(char **path, char *arg)
{
	write(2, "cd: not a directory: ", 21);
	ft_putendl_fd(arg, 2);
	ft_strdel(path);
	return (1);
}

int		msh_nofile(char **path, char *arg)
{
	write(2, "cd: no such file or directory: ", 31);
	if (!ft_strcmp(arg, "-"))
		ft_putendl_fd(*path, 2);
	else
		ft_putendl_fd(arg, 2);
	ft_strdel(path);
	return (1);
}

int		msh_noaccess(char **path, char *arg)
{
	write(2, "cd: permission denied: ", 23);
	ft_putendl_fd(arg, 2);
	ft_strdel(path);
	return (1);
}

int		msh_setenverror(t_shell *shell)
{
	shell->exit_status = 1;
	write(2, "setenv: not a valid identifier", 30);
	ft_putchar_fd('\n', 2);
	return (1);
}
