/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fd_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/12 11:24:19 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 11:24:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"

#include <errno.h>

int		fd_error(char *filename, int ambiguous)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	if (ambiguous)
		ft_putendl_fd("ambiguous redirect", 2);
	else if (errno == EBADF)
		ft_putendl_fd("Bad file descriptor", 2);
	else if (errno == EMFILE)
		ft_putendl_fd("Too many opened fds", 2);
	return (1);
}

void	manage_pipe_fds(t_pipe *p)
{
	if ((*p).input != STDIN_FILENO)
		close((*p).input);
	if ((*p).output != STDOUT_FILENO)
		close((*p).output);
	close((*p).fds[WRITE_END]);
	if ((*p).first != STDIN_FILENO)
		close((*p).first);
	(*p).first = (*p).fds[READ_END];
}

void	save_fd_original_state(t_shell *shell)
{
	int i;

	i = 0;
	while (i < 3)
	{
		shell->fd_orig[i] = -1;
		i++;
	}
}

void	restore_fd_original_state(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (shell->fd_orig[i] != -1)
			close(shell->fd_orig[i]);
		i++;
	}
}

void	rebuild_fd(t_redir *redirlst)
{
	t_redir	*redir;

	redir = redirlst;
	while (redir)
	{
		if (redir->fd > 2)
			close(redir->fd);
		if (redir->io_nbr > 2)
			close(redir->io_nbr);
		redir = redir->next;
	}
}
