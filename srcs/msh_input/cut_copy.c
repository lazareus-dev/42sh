/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cut_copy.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 12:44:45 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:58:40 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <termcap.h>
#define CUT	0
#define COPY	1

static void	util_buffer_before_index(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strdup(shell->input.buffer);
	ft_strdel(&shell->input.buffer);
	shell->input.buffer = ft_strsub(tmp, shell->input.i,
		(shell->input.len - shell->input.i));
	ft_strdel(&tmp);
	shell->input.len = ft_strlen(shell->input.buffer);
	shell->input.end_buf.y = calculate_end_buf_y(shell) + shell->input.start.y;
}

static void	buffer_before_index(t_shell *shell, int job)
{
	ft_strdel(&shell->input.copy_paste);
	if (!shell->input.buffer || !shell->input.buffer[0])
		return ;
	shell->input.copy_paste = ft_strsub(shell->input.buffer, 0, shell->input.i);
	if (job == CUT)
	{
		util_buffer_before_index(shell);
		if (shell->input.buffer && ft_strchr(shell->input.buffer, '\n'))
			shell->input.end_buf.x = nb_char_after_last_bs_n(shell);
		else
		{
			shell->input.end_buf.x -= shell->input.i;
			while (shell->input.end_buf.x < 0)
				shell->input.end_buf.x += shell->input.nb_co + 1;
		}
		shell->input.i = 0;
		util_move(shell->input.start.x, shell->input.start.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
		write(1, shell->input.buffer, ft_strlen(shell->input.buffer));
		shell->input.cursor.x = shell->input.start.x;
		shell->input.cursor.y = shell->input.start.y;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}

static void	buffer_after_index(t_shell *shell, int job)
{
	char	*tmp;

	tmp = NULL;
	ft_strdel(&shell->input.copy_paste);
	shell->input.copy_paste = ft_strsub(shell->input.buffer, shell->input.i,
		(shell->input.len - shell->input.i));
	if (job == CUT)
	{
		tmp = ft_strdup(shell->input.buffer);
		shell->input.end_buf.y = shell->input.cursor.y;
		shell->input.end_buf.x = shell->input.cursor.x;
		ft_strdel(&shell->input.buffer);
		shell->input.buffer = ft_strsub(tmp, 0, shell->input.i);
		ft_strdel(&tmp);
		shell->input.len = ft_strlen(shell->input.buffer);
		shell->input.i = shell->input.len;
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
	}
}

static void	all_buffer(t_shell *shell, int job)
{
	ft_strdel(&shell->input.copy_paste);
	shell->input.copy_paste = ft_strdup(shell->input.buffer);
	if (job == CUT)
	{
		ft_strdel(&shell->input.buffer);
		util_move(shell->input.start.x, shell->input.start.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
		shell->input.i = 0;
		shell->input.len = 0;
		shell->input.cursor.x = shell->input.start.x;
		shell->input.cursor.y = shell->input.start.y;
		shell->input.end_buf.x = shell->input.start.x;
		shell->input.end_buf.y = shell->input.start.y;
	}
}

void		cut_copy_paste(t_shell *shell, char *buf)
{
	if (buf[0] == -61 && buf[1] == -91 && buf[2] == 0)
		all_buffer(shell, CUT);
	else if (buf[0] == -61 && buf[1] == -97 && buf[2] == 0)
		buffer_before_index(shell, CUT);
	else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -126)
		buffer_after_index(shell, CUT);
	else if (buf[0] == -50 && buf[1] == -87 && buf[2] == 0)
		all_buffer(shell, COPY);
	else if (buf[0] == -30 && buf[1] == -119 && buf[2] == -120 && buf[4] == 0)
		buffer_before_index(shell, COPY);
	else if (buf[0] == -61 && buf[1] == -89 && buf[2] == 0)
		buffer_after_index(shell, COPY);
	else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -102 && buf[4] == 0)
		paste_copy(shell, shell->input.copy_paste);
}
