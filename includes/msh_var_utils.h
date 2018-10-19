/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_var_utils.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 16:19:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:52:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_VAR_UTILS_H
# define MSH_VAR_UTILS_H

# define PRIVATE	0
# define EXPORTED	1

t_var	*var_exists(char *var, t_shell *shell);
char	*get_var_name(char *env);
char	*get_var_value(char *env);
int		check_var_name(char *env, char *env_name);
char	*msh_getenv(char *name, t_shell *shell);
int		ft_update_var(t_var *node, char *new_value);
int		add_new_var(char *var, t_headlst *lst, int exported);

#endif
