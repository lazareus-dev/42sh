/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_signal.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 14:57:41 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 14:58:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

void	sig_handlers(void);
void	sigint_handler(int sig);
void	sigtstp_child(int sig);

#endif
