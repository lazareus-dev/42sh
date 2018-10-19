/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_input.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 13:32:11 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 22:31:28 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_input.h"
#include <termcap.h>

static void	update_screen(t_shell *shell)
{
	if (shell->input.end_buf.y + 1 >= shell->input.nb_li)
	{
		util_move(0, shell->input.end_buf.y + 1);
		tputs(tgetstr("sf", NULL), 1, ft_putchar_term);
		shell->input.end_buf.y = shell->input.start.x +
		calculate_end_buf_y(shell);
		shell->input.start.y = shell->input.end_buf.y -
		calculate_end_buf_y(shell);
	}
	else
		util_move(0, shell->input.end_buf.y + 1);
}

int			input_loop(t_shell *shell)
{
	char	buff[BUFFSIZE];

	get_cursor_position(shell, INIT_COORD);
	shell->sigint = 0;
	while (101)
	{
		ft_bzero(buff, BUFFSIZE);
		read(shell->terminal.fd, buff, BUFFSIZE - 1);
		if (ft_isprint(buff[0]))
			process_input_printable(buff[0], shell);
		else if (buff[0] == '\n')
		{
			update_screen(shell);
			process_input_newline(shell);
			return (0);
		}
		else if (buff[0] == 4)
		{
			if (process_input_eof(shell))
				return (EOF);
		}
		else
			move_choice(shell, buff);
	}
	return (0);
}
