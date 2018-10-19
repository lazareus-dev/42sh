/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_signal.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 14:51:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 17:02:30 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../includes/msh_terminal.h"
#include <sys/ioctl.h>
#include <termcap.h>

static void	handle_winch(int sig)
{
	(void)sig;
	signal(SIGWINCH, SIG_IGN);
	window_size();
	signal(SIGWINCH, handle_winch);
}

void		ctrl_c(t_shell *shell)
{
	char	c;

	c = 10;
	shell->sigint = 1;
	ft_strdel(&shell->input.line);
	ft_strdel(&shell->input.buffer);
	ft_strdel(&shell->input.h_tmp);
	ft_strdel(&shell->input.copy_paste);
	shell->input.len = 0;
	shell->input.i = 0;
	ioctl(shell->terminal.fd, TIOCSTI, &c);
}

void		sigint_handler(int sig)
{
	t_shell	*shell;

	shell = get_shell();
	if (sig == SIGINT)
		ctrl_c(shell);
}

void		sig_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, handle_winch);
	signal(SIGUSR1, sigint_handler);
	signal(SIGHUP, sigint_handler);
	signal(SIGIO, sigint_handler);
}
