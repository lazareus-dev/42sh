/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_opt_cdsp.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 15:56:51 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 19:28:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_var_utils.h"

#include <fcntl.h>

static void	detach_hist_node(t_history *history, t_hist *del)
{
	t_hist *prev;
	t_hist *next;

	if (!del)
		return ;
	if ((prev = del->prev))
		prev->next = del->next;
	if ((next = del->next))
		next->prev = del->prev;
	if (history->first == del)
		history->first = next;
	if (history->last == del)
		history->last = prev;
	ft_strdel(&del->line);
	free(del);
}

/*
**  history -d
*/

int			del_one_hist(t_shell *shell)
{
	int		i;
	int		offset;
	t_hist	*del;

	del = shell->history->first;
	offset = (ft_atoi(shell->history->opt_offset) - 1);
	if (offset < 0 || offset >= shell->history->nb_node)
		return (msh_history_error(&shell->history->opt_offset, OUT_OF_RANGE));
	i = -1;
	while (++i < offset && del != NULL)
		del = del->next;
	detach_hist_node(shell->history, del);
	while (i < shell->history->nb_node)
	{
		shell->history->hash_hist[i] = shell->history->hash_hist[i + 1];
		++i;
	}
	shell->history->nb_node -= 1;
	return (0);
}

/*
**  history -s
*/

int			append_arg_to_hist(t_history *history)
{
	if (!history->opt_args)
		return (0);
	ft_strdel(&history->last->line);
	history->last->line = ft_strdup(history->opt_args);
	history->hash_hist[history->nb_node - 1] = history->last->line;
	return (0);
}

/*
**  history -p
*/

int			print_arg_delete_last(t_history *history)
{
	t_hist *new_last;

	ft_putendl(history->opt_args);
	new_last = history->last->prev;
	ft_strdel(&history->last->line);
	free(history->last);
	history->last = new_last;
	history->last->next = NULL;
	return (0);
}

/*
**  history -c
*/

int			clear_history(t_shell *shell)
{
	int		hist_fd;
	char	*file;

	file = msh_getenv("HISTFILE", shell);
	free_histlst(&(shell->history));
	shell->history->nb_node = 0;
	if ((hist_fd = open(file, O_RDONLY | O_WRONLY | O_TRUNC)) < 0)
		return (1);
	else
		close(hist_fd);
	return (0);
}
