/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_error.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 22:26:12 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 18:35:03 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

# define HOME_NOT_SET 	0
# define OLDPWD_NOT_SET 1
# define USAGE			2

# define TERM_NOT_SET	0
# define TERM_ACCESS_DB	1
# define TERM_NOT_FOUND	2
# define GET_ATTR_FAIL	3

void	*msh_cdenverror(int issue);
int		msh_notdir(char **path, char *arg);
int		msh_nofile(char **path, char *arg);
int		msh_noaccess(char **path, char *arg);
int		msh_setenverror(t_shell *shell);
int		cmd_error(char *cmd);
int		fork_error(void);
int		msh_notexec(char *path);
int		msh_exitstatuserror(char *exit);
int		msh_exitargserror(void);

int		term_error(int type);

int		msh_error_identifier(char *id);

int		pipe_error(void);

#endif
