/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_setunsetenv.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 16:01:12 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 11:37:59 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_SETUNSETENV_H
# define MSH_SETUNSETENV_H

int		msh_setenv(char *environ, t_shell *shell);
int		msh_unsetenv(char **args, t_shell *shell);
int		ft_unsetenv(char *env_name, t_headlst *env);
int		ft_setenv(char *name, char *value, t_headlst *env);
char	*get_var_name(char *environ);

#endif
