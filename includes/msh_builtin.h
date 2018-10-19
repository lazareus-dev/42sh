/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_builtin.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 21:28:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 18:35:22 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_BUILTIN_H
# define MSH_BUILTIN_H

int		msh_builtin(char **av, t_shell *shell);
int		is_builtin(char **av);

/*
** msh_echo.c
*/

int		msh_echo(char **msg);

/*
** msh_exit.c
*/

int		msh_exit(char **av, t_shell *shell);

/*
** msh_env.c
*/

int		msh_env(char **args, t_shell *shell);
int		dispatch_env(char **av, t_shell *shell, int fork);

/*
** msh_hash.c
*/

int		msh_hash(char **av, t_shell *shell);

/*
** msh_history.c
*/

int		msh_history(char **av, t_shell *shell);

int		msh_export(char **av, t_shell *shell);

int		msh_unset(char **av, t_shell *shell);

#endif
