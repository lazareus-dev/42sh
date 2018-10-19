/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_exec.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 17:46:38 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 19:27:17 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_EXEC_H
# define MSH_EXEC_H

# define IS_DIR		0
# define OPEN_ERR	1

# define NO_FORK	0
# define FORK_IT	1

# define READ_END	0
# define WRITE_END	1

# define CHILD		0

typedef struct	s_pipe
{
	int			fds[2];
	int			first;
	int			input;
	int			output;
}				t_pipe;

/*
**	Execution functions
*/

int				msh_exec(char *cmd, char **args, t_shell *shell, int fork);
void			exec_all(t_cmds *cmds, t_shell *shell);
int				parse_status(int status);

/*
**	Pipe functions
*/

int				msh_pipe(t_cmds **cmd, t_shell *shell);
void			delete_pipe_nodes(t_cmds **cmds);
void			manage_fd(int *fd[2], int i, int j, int std);
void			forward_piped_cmds(t_cmds **cmds);

/*
**	Redir functions
*/

int				process_redir(t_cmds *cmd);
void			remove_redir(t_cmds *cmd);

/*
**	Dispatch utils
*/

char			*iterate_path(char *cmd, char *path);
char			*get_cmd_path(char *cmd, t_shell *shell);
int				empty_path_env(t_shell *shell);

/*
**	fd functions
*/

void			save_fd_original_state(t_shell *shell);
void			restore_fd_original_state(t_shell *shell);
void			rebuild_fd(t_redir *redirlst);
int				fd_error(char *filename, int ambiguous);
void			manage_pipe_fds(t_pipe *p);

#endif
