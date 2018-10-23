/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_signal.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 11:20:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 11:21:01 by tle-coza    ###    #+. /#+    ###.fr     */
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

void		sig_child_handlers(void)
{
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGUSR1, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGIO, SIG_DFL);
}

void		sig_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, handle_winch);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGIO, SIG_IGN);
}
