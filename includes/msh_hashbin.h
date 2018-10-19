/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_hashbin.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/18 16:41:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/18 16:41:34 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_HASHBIN_H
# define MSH_HASHBIN_H

int	init_bintable(t_shell *shell);
int	reset_bintable(int reinit, t_shell *shell);
int msh_addbin_to_table(char *cmd, char *fullpath);

#endif
