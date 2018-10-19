/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace_delete.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 13:45:10 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/29 13:45:29 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/msh_input.h"

int			nb_chars_between_2_bs_n(t_shell *shell)
{
	char	*buffer;
	int		index;
	int		nb_chars;

	buffer = ft_strdup(shell->input.buffer);
	index = shell->input.i - 1;
	nb_chars = 0;
	buffer[index] = '\0';
	while (index > 0 && buffer[index - 1] != '\n')
		index--;
	if (index == 0)
		nb_chars += shell->input.start.x;
	while (buffer[index])
	{
		index++;
		nb_chars++;
	}
	ft_strdel(&buffer);
	return (nb_chars);
}

static void	move_cursor(t_shell *shell)
{
	if (shell->input.buffer[shell->input.i - 1] == '\n')
	{
		shell->input.cursor.y--;
		shell->input.cursor.x = nb_chars_between_2_bs_n(shell);
		while (shell->input.cursor.x > shell->input.nb_co)
			shell->input.cursor.x -= shell->input.nb_co + 1;
	}
	else if (shell->input.cursor.x == 0)
	{
		shell->input.cursor.y--;
		shell->input.cursor.x = shell->input.nb_co;
	}
	else
	{
		shell->input.cursor.x--;
	}
}

static void	backspace_middle_line(t_shell *shell)
{
	if (shell->input.i > 0)
	{
		move_cursor(shell);
		make_new_buffer(shell, BACKSPACE);
		shell->input.len--;
		shell->input.i--;
		shell->input.end_buf.y = calculate_end_buf_y(shell) +
		shell->input.start.y;
		if (ft_strchr(shell->input.buffer, '\n'))
			shell->input.end_buf.x = nb_char_after_last_bs_n(shell);
		else
		{
			shell->input.end_buf.x--;
			if (shell->input.end_buf.x < 0)
				shell->input.end_buf.x += shell->input.nb_co + 1;
		}
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}

void		backspace(t_shell *shell)
{
	deplace_cursor_win_size(shell);
	if (shell->input.i == shell->input.len && shell->input.len > 0)
	{
		move_cursor(shell);
		make_new_buffer(shell, BACKSPACE);
		shell->input.i--;
		shell->input.len--;
		get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
	else
		backspace_middle_line(shell);
}

void		delete(t_shell *shell)
{
	int		x;
	int		y;

	deplace_cursor_win_size(shell);
	if (shell->input.len > 0 && shell->input.i != shell->input.len)
	{
		x = shell->input.cursor.x;
		y = shell->input.cursor.y;
		make_new_buffer(shell, DELETE);
		shell->input.len--;
		shell->input.end_buf.y = calculate_end_buf_y(shell) +
		shell->input.start.y;
		if (ft_strchr(shell->input.buffer, '\n'))
			shell->input.end_buf.x = nb_char_after_last_bs_n(shell);
		else
		{
			shell->input.end_buf.x--;
			if (shell->input.end_buf.x < 0)
				shell->input.end_buf.x += shell->input.nb_co + 1;
		}
		shell->input.cursor.x = x;
		shell->input.cursor.y = y;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}
