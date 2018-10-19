/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_navigation.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/11 17:54:58 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 18:59:43 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include <termcap.h>

void		history_up(t_shell *shell)
{
	if (!shell->history->last ||
			shell->history->current == shell->history->first)
		return ;
	if (!shell->history->current)
		shell->history->current = shell->history->last;
	else
	{
		if (shell->history->current->prev != NULL)
			shell->history->current = shell->history->current->prev;
	}
	if (shell->history->current)
	{
		util_move(shell->input.start.x, shell->input.start.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
		ft_strdel(&shell->input.buffer);
		shell->input.buffer = ft_strdup(shell->history->current->line);
		put_line(shell->input.buffer);
		shell->input.len = ft_strlen(shell->input.buffer);
		shell->input.i = shell->input.len;
		get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}

static void	util_history_down(t_shell *shell)
{
	ft_strdel(&shell->input.buffer);
	shell->input.buffer = ft_strdup(shell->input.h_tmp);
	shell->input.first_call_history = 1;
	ft_strdel(&shell->input.h_tmp);
	put_line(shell->input.buffer);
	shell->input.len = ft_strlen(shell->input.buffer);
	shell->input.i = shell->input.len;
	shell->input.end_buf.x = shell->input.start.x + shell->input.len;
	shell->input.cursor.x = shell->input.end_buf.x;
}

void		history_down(t_shell *shell)
{
	if (!shell->history->last)
		return ;
	if (shell->history->current)
	{
		shell->history->current = shell->history->current->next;
		util_move(shell->input.start.x, shell->input.start.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
		if (shell->history->current)
		{
			ft_strdel(&shell->input.buffer);
			shell->input.buffer = ft_strdup(shell->history->current->line);
			put_line(shell->input.buffer);
			shell->input.len = ft_strlen(shell->input.buffer);
			shell->input.i = shell->input.len;
			shell->input.end_buf.x = shell->input.start.x + shell->input.len;
			shell->input.cursor.x = shell->input.end_buf.x;
		}
		else
			util_history_down(shell);
		get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}
