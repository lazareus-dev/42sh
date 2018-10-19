/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_navigation.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 13:01:56 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 18:10:07 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include <termcap.h>

void		go_right(t_shell *shell)
{
	if (shell->input.buffer[shell->input.i] == '\n')
	{
		shell->input.cursor.y++;
		shell->input.cursor.x = 0;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
		shell->input.i++;
	}
	else if (shell->input.cursor.x == shell->input.nb_co)
	{
		shell->input.cursor.x = 0;
		shell->input.cursor.y++;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
		shell->input.i++;
	}
	else
	{
		shell->input.cursor.x++;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
		shell->input.i++;
	}
}

void		go_left(t_shell *shell)
{
	if (shell->input.buffer[shell->input.i - 1] == '\n')
	{
		shell->input.cursor.y--;
		shell->input.cursor.x = nb_chars_between_2_bs_n(shell);
		while (shell->input.cursor.x > shell->input.nb_co)
			shell->input.cursor.x -= shell->input.nb_co + 1;
	}
	else
	{
		shell->input.cursor.x--;
		if (shell->input.cursor.x < 0)
			shell->input.cursor.y--;
		while (shell->input.cursor.x < 0)
			shell->input.cursor.x += shell->input.nb_co + 1;
	}
	shell->input.i--;
	util_move(shell->input.cursor.x, shell->input.cursor.y);
}

static void	go_end(t_shell *shell)
{
	util_move(shell->input.end_buf.x, shell->input.end_buf.y);
	shell->input.cursor.x = shell->input.end_buf.x;
	shell->input.cursor.y = shell->input.end_buf.y;
	shell->input.i = shell->input.len;
}

void		deplace_cursor(t_shell *shell, char *buf)
{
	if (buf[2] == 67 && shell->input.i < shell->input.len)
		go_right(shell);
	if (buf[2] == 68 && shell->input.i > 0)
		go_left(shell);
	if (buf[2] == 72)
	{
		util_move(shell->input.start.x, shell->input.start.y);
		shell->input.cursor.x = shell->input.start.x;
		shell->input.cursor.y = shell->input.start.y;
		shell->input.i = 0;
	}
	if (buf[2] == 70)
		go_end(shell);
	if (buf[2] == 65 || (buf[2] == 53 && buf[3] == 126))
	{
		if (shell->input.first_call_history)
		{
			shell->input.h_tmp = ft_strdup(shell->input.buffer);
			shell->input.first_call_history--;
		}
		history_up(shell);
	}
	if (buf[2] == 66 || (buf[2] == 54 && buf[3] == 126))
		history_down(shell);
}
