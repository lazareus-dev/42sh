/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_opt_anrw.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 15:43:38 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 15:43:41 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_var_utils.h"

/*
**  history -w
*/

int			append_hist_to_file(t_shell *shell)
{
	t_hist	*run;
	char	*file;
	int		hist_fd;

	if (!(file = shell->history->opt_args[0]))
		file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_write(file, FILE_APPEND)) < 0)
		return (1);
	run = shell->history->first;
	while (run)
	{
		ft_putendl_fd(run->line, hist_fd);
		run = run->next;
	}
	close(hist_fd);
	return (0);
}

/*
**  history -a
*/

int			append_latest_to_file(t_shell *shell)
{
	char	*file;
	int		hist_fd;
	int		i;

	if (!(file = shell->history->opt_args[0]))
		file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_write(file, FILE_APPEND)) < 0)
		return (1);
	while (shell->history->hash_hist[shell->history->index_at_startup])
	{
		i = shell->history->index_at_startup;
		ft_putendl_fd(shell->history->hash_hist[i], hist_fd);
		shell->history->index_at_startup += 1;
	}
	close(hist_fd);
	return (0);
}

static int	clear(int fd, char **line)
{
	close(fd);
	ft_strdel(line);
	return (1);
}

/*
**  history -n
*/

int			append_latest_to_history(t_shell *shell)
{
	char	*file;
	char	*line;
	int		hist_fd;
	int		i;

	if (!(file = shell->history->opt_args[0]))
		file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_read(file)) < 0)
		return (1);
	i = 1;
	line = NULL;
	while ((i++ <= shell->history->index_at_startup)
	&& (get_next_line(hist_fd, &line) > 0))
		ft_strdel(&line);
	while (get_next_line(hist_fd, &line) > 0)
	{
		if (!ft_strequ(line, "\0"))
			if (add_hist_to_lst(line, shell))
				return (clear(hist_fd, &line));
		ft_strdel(&line);
	}
	close(hist_fd);
	return (0);
}

/*
**  history -r
*/

int			append_file_to_hist(char *file, t_shell *shell)
{
	char	*line;
	int		hist_fd;

	if (file == NULL)
		file = msh_getenv("HISTFILE", shell);
	if ((hist_fd = ft_get_fd_read(file)) < 0)
		return (1);
	line = NULL;
	while (get_next_line(hist_fd, &line) > 0)
	{
		if (!ft_strequ(line, "\0"))
			if (add_hist_to_lst(line, shell))
				return (clear(hist_fd, &line));
		ft_strdel(&line);
	}
	close(hist_fd);
	return (0);
}
