/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_terminal.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 15:58:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:55:26 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_terminal.h"

#include <termcap.h>
#include <fcntl.h>

static int	get_termtype(void)
{
	char	*termtype;
	int		ret;

	if (!(termtype = getenv("TERM")))
	{
		term_error(TERM_NOT_SET);
		termtype = "vt100";
	}
	ret = tgetent(NULL, termtype);
	if (ret == -1)
		return (term_error(TERM_ACCESS_DB));
	else if (ret == 0)
		return (term_error(TERM_NOT_FOUND));
	return (0);
}

int			set_raw_term(t_shell *shell)
{
	if (tcsetattr(shell->terminal.fd, TCSANOW,
				&(shell->terminal.termios)) == -1)
		return (1);
	return (0);
}

int			set_canonical_term(t_shell *shell)
{
	if (tcsetattr(shell->terminal.fd, TCSAFLUSH,
				&(shell->terminal.orig_termios)) == -1)
		return (1);
	return (0);
}

int			init_termios(t_shell *shell)
{
	get_termtype();
	if (isatty(STDIN_FILENO) == 0)
		return (term_error(4));
	shell->terminal.fd = STDIN_FILENO;
	if (tcgetattr(shell->terminal.fd, &(shell->terminal.orig_termios)) == -1)
		return (term_error(GET_ATTR_FAIL));
	if (tcgetattr(shell->terminal.fd, &(shell->terminal.termios)) == -1)
		return (term_error(GET_ATTR_FAIL));
	shell->terminal.termios.c_lflag &= ~(ICANON);
	shell->terminal.termios.c_lflag &= ~(ECHO);
	shell->terminal.termios.c_cc[VMIN] = 1;
	shell->terminal.termios.c_cc[VTIME] = 0;
	return (0);
}
