/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_lstenv.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 16:58:24 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 15:56:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_LSTENV_H
# define MSH_LSTENV_H

# include "minishell.h"

void		init_variron(t_shell *shell);
char		**lst_to_env(t_headlst *lst);
void		free_envlst(t_headlst *lst);
t_var		*new_env(char *environ);
void		push_back(t_headlst *lst, t_var *elem);

#endif
