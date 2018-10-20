/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_history.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 11:38:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 17:50:19 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_var_utils.h"

char	*get_hist(int index, t_history *history)
{
	char	*histline;

	if (index >= history->nb_node || index < 0)
		return (NULL);
	histline = history->hash_hist[index];
	return (histline);
}

int		init_hash_hist(t_history **history)
{
	t_hist	*node;
	int		i;

	if (!((*history)->hash_hist = ft_strtab_alloc(
		(*history)->nb_node + HASH_HIST_MIN)))
		return (1);
	(*history)->hash_hist_size = (*history)->nb_node + HASH_HIST_MIN;
	node = (*history)->first;
	i = 0;
	while (node)
	{
		(*history)->hash_hist[i] = node->line;
		node = node->next;
		++i;
	}
	(*history)->index_at_startup = (*history)->nb_node;
	return (0);
}

/*
**	Get the history entries from the file described by char *file
**	or the file described by $HISTFILE if char *file is NULL
*/

int		fill_history_from_file(t_history **history, char *file, t_shell *shell)
{
	t_hist	*node;
	char	*line;
	int		hist_fd;

	if (file == NULL)
		file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_read(file)) < 0)
		return (1);
	line = NULL;
	while (get_next_line(hist_fd, &line) > 0)
	{
		if (ft_strcmp(line, "\0"))
		{
			if ((node = new_hist(line)))
			{
				push_back_hist(history, node);
				++((*history)->nb_node);
			}
		}
		ft_strdel(&line);
	}
	close(hist_fd);
	return (0);
}

int		init_history(t_shell *shell)
{
	if (!(shell->history = (t_history *)malloc(sizeof(t_history))))
		return (1);
	shell->history->first = NULL;
	shell->history->last = NULL;
	shell->history->current = NULL;
	shell->history->nb_node = 0;
	fill_history_from_file(&(shell->history), NULL, shell);
	init_hash_hist(&(shell->history));
	shell->history->opt = 0;
	shell->history->opt_offset = 0;
	shell->history->opt_args = NULL;
	return (0);
}
