/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_terminal.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 16:00:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 16:01:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_TERMINAL_H
# define MSH_TERMINAL_H

int		init_termios(t_shell *shell);
int		set_raw_term(t_shell *shell);
int		set_canonical_term(t_shell *shell);

#endif
