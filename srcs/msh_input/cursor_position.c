/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 17:38:30 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 18:04:00 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include <termcap.h>
#include <sys/ioctl.h>

static void	position(t_shell *shell)
{
	char	buf[40];
	int		i;

	i = 0;
	ft_bzero(buf, 9);
	write(shell->terminal.fd, "\033[6n", 4);
	read(shell->terminal.fd, buf, sizeof(buf));
	shell->input.cursor.y = ft_atoi(buf + 2) - 1;
	while (buf[i] && buf[i] != 59)
		i++;
	shell->input.cursor.x = ft_atoi(buf + i + 1) - 1;
}

static void	update_start_end(t_shell *shell)
{
	struct winsize	wind;

	ioctl(0, TIOCGWINSZ, &wind);
	if (shell->input.cursor.x == shell->input.len_prompt - 1)
	{
		shell->input.cursor.x = 0;
		if (shell->input.cursor.y + 1 == wind.ws_row)
			tputs(tgetstr("sf", NULL), 1, ft_putchar_term);
		else
			shell->input.cursor.y++;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
	shell->input.start.y = shell->input.cursor.y;
	shell->input.start.x = shell->input.cursor.x;
	shell->input.end_buf.y = shell->input.cursor.y;
	shell->input.end_buf.x = shell->input.cursor.x;
}

static void	calculate_end_limit(t_shell *shell)
{
	shell->input.end_buf.y = shell->input.cursor.y;
	shell->input.end_buf.x = shell->input.cursor.x;
	if (shell->input.start.x + (int)shell->input.len ==
		(shell->input.end_buf.y - shell->input.start.y) * shell->input.nb_co
		+ shell->input.nb_co + 1 + (shell->input.end_buf.y -
			shell->input.start.y))
	{
		if (shell->input.end_buf.y + 1 == shell->input.nb_li)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar_term);
			shell->input.start.y--;
		}
		else
			shell->input.end_buf.y++;
		shell->input.end_buf.x = 0;
		shell->input.cursor.y = shell->input.end_buf.y;
		shell->input.cursor.x = shell->input.end_buf.x;
	}
	shell->input.start.y = shell->input.end_buf.y - calculate_end_buf_y(shell);
}

int			calculate_end_buf_y(t_shell *shell)
{
	int		i;
	int		len_line;
	int		y;

	i = 0;
	y = 0;
	len_line = shell->input.start.x;
	if (!shell->input.buffer || !shell->input.buffer[0])
		return (0);
	while (shell->input.buffer[i])
	{
		if (shell->input.buffer[i] == '\n')
		{
			y++;
			len_line = -1;
		}
		if (len_line >= shell->input.nb_co)
		{
			y++;
			len_line = -1;
		}
		len_line++;
		i++;
	}
	return (y);
}

void		get_cursor_position(t_shell *shell, short i)
{
	position(shell);
	position(shell);
	while (shell->input.cursor.y < 0 || shell->input.cursor.x < 0)
		position(shell);
	if (i == CURRENT_LINE_END_LIMIT)
		calculate_end_limit(shell);
	if (i == INIT_COORD)
		update_start_end(shell);
}
