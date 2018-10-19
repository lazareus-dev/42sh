/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_choice.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 19:53:15 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 22:32:36 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <termcap.h>

static void	deplace_word_right(t_shell *shell)
{
	while (shell->input.i < shell->input.len &&
		shell->input.buffer[shell->input.i] != ' ' &&
		shell->input.buffer[shell->input.i] != '\n')
	{
		go_right(shell);
	}
	while (shell->input.i < shell->input.len &&
		(shell->input.buffer[shell->input.i] == ' ' ||
			shell->input.buffer[shell->input.i] == '\n'))
	{
		go_right(shell);
	}
}

static void	deplace_word_left(t_shell *shell)
{
	while (shell->input.i > 0 && shell->input.buffer[shell->input.i] != ' ' &&
		shell->input.buffer[shell->input.i] != '\n')
	{
		go_left(shell);
	}
	while (shell->input.i > 0 && (shell->input.buffer[shell->input.i] == ' ' ||
		shell->input.buffer[shell->input.i] == '\n'))
	{
		go_left(shell);
	}
}

static void	deplace_line_up(t_shell *shell)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	if (shell->input.cursor.y > shell->input.start.y)
	{
		y = shell->input.cursor.y - 1;
		x = shell->input.cursor.x;
		while (shell->input.cursor.y > y)
		{
			go_left(shell);
			while (shell->input.cursor.x != x && shell->input.i > 0)
			{
				if (shell->input.cursor.y == y && shell->input.cursor.x < x)
					break ;
				if (y == shell->input.start.y)
				{
					if (shell->input.cursor.x - shell->input.start.x == x)
						break ;
				}
				go_left(shell);
			}
		}
	}
}

static void	deplace_line_down(t_shell *shell)
{
	int		y;
	int		x;

	y = shell->input.cursor.y + 1;
	x = shell->input.cursor.x;
	if (shell->input.cursor.y < shell->input.end_buf.y)
	{
		while (shell->input.cursor.y < y)
		{
			go_right(shell);
			while (shell->input.cursor.x != x && shell->input.i <
				shell->input.len)
			{
				if (shell->input.buffer[shell->input.i] == '\n')
					break ;
				if (shell->input.cursor.y == shell->input.start.y + 1)
				{
					if (shell->input.cursor.x + shell->input.start.x == x)
						break ;
				}
				go_right(shell);
			}
		}
	}
}

void		move_choice(t_shell *shell, char *buf)
{
	if (shell->input.print)
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_term);
		return ;
	}
	if (buf[0] == 127)
		backspace(shell);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
		delete(shell);
	else if (buf[0] == 27 && buf[1] == 91)
		deplace_cursor(shell, buf);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67)
		deplace_word_right(shell);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68)
		deplace_word_left(shell);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 65)
		deplace_line_up(shell);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 66)
		deplace_line_down(shell);
	else if (buf[0] == -61 || buf[0] == -30 || buf[0] == -50)
		cut_copy_paste(shell, buf);
	else if (buf[0] == 9)
		msh_completion(shell);
	else if (buf[0] == 12 && buf[1] == 0 && buf[2] == 0)
		clear_screen(shell);
}
