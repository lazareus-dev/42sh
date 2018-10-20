/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   window_size.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 13:10:54 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 18:22:04 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <sys/ioctl.h>
#include <termcap.h>

static void	update_window(t_shell *shell, int nb_col, int nb_lin)
{
	if (shell->input.print)
		ft_putstr_fd("\e[H\e[J", 0);
	if (nb_col - 1 != shell->input.nb_co)
	{
		shell->input.nb_co = nb_col - 1;
		if (shell->input.print)
			util_move(0, 0);
		else
			util_move(0, shell->input.start.y);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_term);
		if (shell->input.prompt == PROMPT)
			prompt(shell);
		else
			reprompt(shell, shell->input.prompt);
		get_cursor_position(shell, INIT_COORD);
		put_line(shell->input.buffer);
		get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
		shell->input.i = shell->input.len;
		shell->input.print = 0;
	}
	shell->input.nb_li = nb_lin;
	shell->input.nb_co = nb_col - 1;
}

void		window_size(void)
{
	struct winsize	wind;
	t_shell			*shell;

	if (!(shell = get_shell()))
		return ;
	ioctl(0, TIOCGWINSZ, &wind);
	if (wind.ws_row > shell->input.nb_li)
	{
		shell->input.start.y += wind.ws_row - shell->input.nb_li;
		shell->input.cursor.y += wind.ws_row - shell->input.nb_li;
		shell->input.end_buf.y += wind.ws_row - shell->input.nb_li;
	}
	else if (wind.ws_row < shell->input.nb_li)
	{
		if (shell->input.end_buf.y != 0)
		{
			shell->input.cursor.y = (wind.ws_row - 1) -
			(shell->input.end_buf.y - shell->input.cursor.y);
			shell->input.end_buf.y = wind.ws_row - 1;
			shell->input.start.y = wind.ws_row - 1 -
			check_size(shell, shell->input.buffer, shell->input.start.x);
		}
	}
	get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
	update_window(shell, wind.ws_col, wind.ws_row);
}
