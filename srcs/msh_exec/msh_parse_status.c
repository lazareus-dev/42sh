/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_parse_status.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 16:19:47 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 16:19:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigerror(char *err, int status)
{
	ft_putstr_fd(err, 2);
	ft_putnbr_fd(status, 2);
	ft_putchar_fd('\n', 2);
}

int			parse_status(int status)
{
	int		ret;

	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 6)
			sigerror("Abort trap: ", 6);
		else if (WTERMSIG(status) == 8)
			sigerror("Floating point exception: ", 8);
		else if (WTERMSIG(status) == 9)
			sigerror("Killed: ", 9);
		else if (WTERMSIG(status) == 10)
			sigerror("Bus error: ", 10);
		else if (WTERMSIG(status) == 11)
			sigerror("Segmentation fault: ", 11);
		else if (WTERMSIG(status) == 13)
			sigerror("Broken pipe: ", 13);
		ret = status + 128;
	}
	else
		ret = WEXITSTATUS(status);
	return (ret);
}
