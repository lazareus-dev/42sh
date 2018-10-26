/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   apply_redir.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/11 14:39:14 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 14:39:15 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_exec.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_error.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static int	file_error(char *filename, int type)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	if (type == IS_DIR)
		ft_putendl_fd("Is a directory", 2);
	if (type == OPEN_ERR && errno == ENOENT)
		ft_putendl_fd("No such file or directory", 2);
	else if (type == OPEN_ERR && errno == EACCES)
		ft_putendl_fd("Permission denied", 2);
	return (1);
}

/*
**	Handle [n]<<[delimiter]
*/

static int	handle_here_doc(t_redir *redir)
{
	int		ret;
	int		fd[2];

	if (pipe(fd) < 0)
		return (pipe_error());
	if (redir->hdoc.here_doc)
		write(fd[WRITE_END], redir->hdoc.here_doc,
			ft_strlen(redir->hdoc.here_doc));
	close(fd[WRITE_END]);
	ret = dup2(fd[READ_END], redir->io_nbr);
	close(fd[READ_END]);
	if (ret < 0)
		return (fd_error(redir->filename, 0));
	return (0);
}

/*
**	Handle [n]>[word], [n]>>[word], [n]<[word], [n]<>[word]
*/

static int	handle_file(t_redir *redir)
{
	if (redir->type == GREAT)
	{
		if (ft_is_dir(redir->filename))
			return (file_error(redir->filename, IS_DIR));
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (redir->type == DGREAT)
	{
		if (ft_is_dir(redir->filename))
			return (file_error(redir->filename, IS_DIR));
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (redir->type == LESS)
		redir->fd = open(redir->filename, O_RDONLY);
	else if (redir->type == LESSGREAT)
		redir->fd = open(redir->filename, O_RDWR);
	if (redir->fd < 0)
		return (file_error(redir->filename, OPEN_ERR));
	if (dup2(redir->fd, redir->io_nbr) < 0)
		return (file_error(redir->filename, 0));
	return (0);
}

/*
**	Handle [n]>&[word]
*/

static int	handle_aggreg(t_redir *redir)
{
	if (redir->filename[0] == '-')
	{
		close(redir->io_nbr);
		return (0);
	}
	else if (redir->filename[0] && !ft_isdigit(redir->filename[0]))
		return (fd_error(redir->filename, 1));
	else
		redir->fd = ft_atoi(redir->filename);
	if ((dup2(redir->fd, redir->io_nbr)) < 0)
		return (fd_error(redir->filename, 0));
	return (0);
}

/*
**	Performs redirections from the redirlst
**	Removes the no more useful REDIR nodes from the tokens
*/

int			process_redir(t_cmds *cmd)
{
	t_redir	*redir;
	int		ret;

	ret = 0;
	redir = cmd->redirlst;
	while (redir && ret == 0)
	{
		dprintf(2, "process file = [%s]\n", redir->filename);
		if (redir->type == GREATAND || redir->type == LESSAND)
			ret = handle_aggreg(redir);
		else if (redir->type == DLESS || redir->type == DLESSDASH)
			ret = handle_here_doc(redir);
		else
			ret = handle_file(redir);
		if (ret == 0)
			redir = redir->next;
	}
	remove_redir_nodes(cmd);
	return (ret);
}
