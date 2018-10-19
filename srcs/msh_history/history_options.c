/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_options.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 15:18:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:56:58 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_var_utils.h"

int	msh_history_error(char **av, int status)
{
	ft_putstr_fd("lsh: history: ", 2);
	if (status == TOO_MANY_ARG)
		ft_putendl_fd("too many arguments", 2);
	else if (status == TOO_MANY_OPT)
		ft_putendl_fd("cannot use more than one of -anrw", 2);
	else
		ft_putstr_fd(av[0], 2);
	if (status == NON_NUM_ARG)
		ft_putendl_fd(": numeric argument required", 2);
	else if (status == OUT_OF_RANGE)
		ft_putendl_fd(": history position out of range", 2);
	else if (status == REQUIRE_ARG)
		ft_putendl_fd(": option require an argument", 2);
	if (status == INVALID_OPT)
		ft_putendl_fd(": invalid option\n" HIST_USAGE1 HIST_USAGE2, 2);
	return (1);
}

int	print_cropped_history(char **av, t_shell *shell)
{
	int	i;
	int	start;

	if (av[1])
		return (msh_history_error(NULL, TOO_MANY_ARG));
	i = 0;
	if (av[0][0] == '+')
		++i;
	while (av[0][i])
		if (!ft_isdigit(av[0][i++]))
			return (msh_history_error(av, NON_NUM_ARG));
	start = (shell->history->nb_node) - ft_atoi(av[0]);
	if (start < 0)
		start = 0;
	return (print_history(shell->history, start));
}

int	process_history_options(t_shell *shell)
{
	int ret;

	ret = 0;
	if (shell->history->opt & HOPT_C)
		ret = clear_history(shell);
	if (shell->history->opt & HOPT_D)
		ret = del_one_hist(shell);
	if (shell->history->opt & HOPT_S)
		ret = append_arg_to_hist(shell->history);
	if (shell->history->opt & HOPT_P)
		ret = print_arg_delete_last(shell->history);
	if (shell->history->opt & HOPT_R)
		ret = append_file_to_hist(shell->history->opt_arg, shell);
	if (shell->history->opt & HOPT_W)
		ret = append_hist_to_file(shell);
	if (shell->history->opt & HOPT_A)
		ret = append_latest_to_file(shell);
	if (shell->history->opt & HOPT_N)
		return (append_latest_to_history(shell));
	return (ret);
}

int	history_options(char **av, t_shell *shell)
{
	if (!av || !av[0])
		return (1);
	if (av[0][0] == '+' || ft_isdigit(av[0][0]))
		return (print_cropped_history(av, shell));
	if (get_hopt(av, shell))
		return (1);
	return (process_history_options(shell));
}
