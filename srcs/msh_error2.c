/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_error2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 22:18:25 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 11:28:38 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <errno.h>

int		cmd_error(char *cmd)
{
	write(2, "lsh: command not found: ", 24);
	ft_putendl_fd(cmd, 2);
	return (127);
}

int		fork_error(void)
{
	write(2, "lsh: fork: ", 11);
	if (errno == EAGAIN)
		ft_putstr_fd("Resource temporarily unavailable", 2);
	ft_putchar('\n');
	while (wait(NULL) > 0)
		;
	return (1);
}

int		msh_notexec(char *path)
{
	char *cmd;

	write(2, "lsh: permission denied: ", 24);
	cmd = ft_strrchr(path, '/');
	if (cmd)
		ft_putendl_fd((cmd + 1), 2);
	else
		ft_putendl_fd(path, 2);
	return (126);
}

int		msh_exitstatuserror(char *exit)
{
	write(2, "exit: ", 6);
	ft_putstr_fd(exit, 2);
	write(2, ": numeric argument required\n", 28);
	return (255);
}

int		msh_exitargserror(void)
{
	write(2, "exit: ", 6);
	write(2, "too many arguments\n", 19);
	return (1);
}
