/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_input_printable.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 15:47:23 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/29 15:47:43 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include "../../includes/msh_lexer.h"
#include <termcap.h>

static int	insert_char_at(t_shell *shell, char c)
{
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strsub(shell->input.buffer, 0, shell->input.i);
	end = ft_strsub(shell->input.buffer, shell->input.i,
	(shell->input.len - ft_strlen(start)));
	tmp = append_char(start, c);
	if (end)
		tmp = ft_str_joinordup(tmp, end);
	ft_strdel(&shell->input.buffer);
	shell->input.buffer = tmp;
	tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
	ft_putchar(c);
	if (end)
	{
		ft_putstr(end);
		ft_strdel(&end);
	}
	return (0);
}

static void	update_cursor_and_end_buf(t_shell *shell)
{
	shell->input.end_buf.y = calculate_end_buf_y(shell) + shell->input.start.y;
	if (shell->input.end_buf.y >= shell->input.nb_li)
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar_term);
		shell->input.end_buf.y--;
		shell->input.cursor.y--;
	}
	if (shell->input.end_buf.y + 1 >= shell->input.nb_li)
		shell->input.start.y = shell->input.end_buf.y -
	calculate_end_buf_y(shell);
	if (shell->input.end_buf.x >= shell->input.nb_co)
		shell->input.end_buf.x = -1;
	if (ft_strchr(shell->input.buffer, '\n'))
		shell->input.end_buf.x = nb_char_after_last_bs_n(shell);
	else
		shell->input.end_buf.x++;
	if (shell->input.cursor.x >= shell->input.nb_co)
	{
		shell->input.cursor.y++;
		shell->input.cursor.x = 0;
	}
	else
		shell->input.cursor.x++;
}

int			process_input_printable(char c, t_shell *shell)
{
	if (check_size(shell, shell->input.buffer, shell->input.start.x) >=
		shell->input.nb_li - 1)
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_term);
		return (1);
	}
	insert_char_at(shell, c);
	shell->input.i++;
	shell->input.len++;
	update_cursor_and_end_buf(shell);
	util_move(shell->input.cursor.x, shell->input.cursor.y);
	return (0);
}

int			process_input_newline(t_shell *shell)
{
	shell->history->current = NULL;
	shell->input.first_call_history = 1;
	ft_strdel(&shell->input.h_tmp);
	shell->input.buffer = append_char(shell->input.buffer, '\n');
	shell->input.line = ft_str_joinordup(shell->input.line,
		shell->input.buffer);
	ft_strdel(&shell->input.buffer);
	shell->input.len = 0;
	shell->input.i = 0;
	return (0);
}

int			process_input_eof(t_shell *shell)
{
	if (!shell->input.buffer || !shell->input.buffer[0])
		return (EOF);
	else
		return (0);
}
