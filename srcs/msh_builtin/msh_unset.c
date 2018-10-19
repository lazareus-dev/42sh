/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_unset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:40:48 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 18:41:11 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_setunsetenv.h"

int		msh_unset(char **args, t_shell *shell)
{
	int		i;
	int		err;

	if (!args || !*args)
		return (0);
	err = 0;
	i = 0;
	while (args[i])
	{
		if (!ft_is_posixname(args[i]))
		{
			err = msh_error_identifier(args[i++]);
			continue ;
		}
		if (ft_strequ(args[i], "PATH"))
			reset_bintable(0, shell);
		if (ft_unsetenv(args[i], &shell->env))
			ft_unsetenv(args[i], &shell->local_var);
		++i;
	}
	return (err);
}
