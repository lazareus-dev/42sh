/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_opt_utils.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/27 14:44:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 14:44:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

int	get_opt_offset(char **av, t_shell *shell)
{
	shell->history->opt |= HOPT_D;
	if (av[0][2])
		shell->history->opt_offset = &(av[0][2]);
	else if (!(shell->history->opt_offset = av[1]))
		return (msh_history_error(av, REQUIRE_ARG));
	return (0);
}

int	parse_hopt(char **av, t_shell *shell)
{
	char opt;

	if (!(opt = av[0][1]))
		return (0);
	if (opt == 'c')
		shell->history->opt |= HOPT_C;
	else if (opt == 'd')
		return (get_opt_offset(av, shell));
	else if (opt == 'a')
		shell->history->opt |= HOPT_A;
	else if (opt == 'n')
		shell->history->opt |= HOPT_N;
	else if (opt == 'r')
		shell->history->opt |= HOPT_R;
	else if (opt == 'w')
		shell->history->opt |= HOPT_W;
	else if (opt == 's')
		shell->history->opt |= HOPT_S;
	else if (opt == 'p')
		shell->history->opt |= HOPT_P;
	else
		return (msh_history_error(av, INVALID_OPT));
	if (ft_strchr("anrwsp", opt))
		shell->history->opt_arg = av[1];
	return (0);
}

int	get_hopt(char **av, t_shell *shell)
{
	int opt;

	if (!av || !av[0])
		return (1);
	if (av[0][0] != '-')
		return (msh_history_error(av, NON_NUM_ARG));
	while (*av)
	{
		if (av[0][0] == '-')
			if (parse_hopt(av, shell))
				return (1);
		av++;
	}
	opt = shell->history->opt;
	if ((((opt & HOPT_A) != 0)
	+ ((opt & HOPT_N) != 0)
	+ ((opt & HOPT_R) != 0)
	+ ((opt & HOPT_W) != 0)) > 1)
		return (msh_history_error(NULL, TOO_MANY_OPT));
	return (0);
}
