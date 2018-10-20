/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_history.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 11:38:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 18:43:46 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_var_utils.h"

void	backup_history(t_shell *shell)
{
	int		hist_fd;
	char	*file;
	t_hist	*hist;

	file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_write(file, FILE_TRUNC)) < 0)
		return ;
	hist = shell->history->first;
	while (hist)
	{
		ft_putendl_fd(hist->line, hist_fd);
		hist = hist->next;
	}
}

int		add_hist_to_table(t_history **history, char *line)
{
	if ((*history)->hash_hist_size <= (*history)->nb_node + 1)
	{
		free((*history)->hash_hist);
		(*history)->hash_hist = NULL;
		init_hash_hist(history);
	}
	else
		(*history)->hash_hist[(*history)->nb_node] = line;
	return (0);
}

int		add_hist_to_lst(char *line, t_shell *shell)
{
	t_hist	*node;

	if (!shell->history)
		return (1);
	if ((node = new_hist(line)))
	{
		push_back_hist(&shell->history, node);
		add_hist_to_table(&(shell->history), node->line);
		++(shell->history->nb_node);
	}
	else
		return (1);
	return (0);
}

int		print_history(t_history *history, int start)
{
	char		**table;
	int			margin;
	int			i;

	if (!history)
		return (1);
	table = history->hash_hist;
	margin = ft_nbr_len(history->nb_node) + 2;
	i = start;
	while (i < history->nb_node)
	{
		ft_printf("%*d  ", margin, ++i);
		ft_putstr(table[i - 1]);
		ft_putchar('\n');
	}
	return (0);
}

/*
**	history built-in entry point
*/

int		msh_history(char **av, t_shell *shell)
{
	int	ret;

	if (!shell->history)
		return (1);
	shell->history->opt = 0;
	if (!av || !av[0])
		ret = print_history(shell->history, 0);
	else if (av && av[0])
		ret = history_options(av, shell);
	else
		ret = 0;
	free(shell->history->opt_args);
	return (ret);
}
