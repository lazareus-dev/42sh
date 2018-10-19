/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_exit.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:06:33 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/13 17:28:51 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_error.h"

/*
** exit built-in
*/

int		msh_exit(char **av, t_shell *shell)
{
	int i;

	i = 0;
	if (av && av[0])
	{
		if (av[1])
			return (msh_exitargserror());
		if (av[0][0] == '+' || av[0][0] == '-')
			++i;
		while (av[0][i])
			if (!ft_isdigit(av[0][i++]))
			{
				shell->exit = 1;
				return (msh_exitstatuserror(av[0]));
			}
		shell->exit_status = (unsigned char)ft_atoi(av[0]);
	}
	shell->exit = 1;
	return (shell->exit_status);
}
