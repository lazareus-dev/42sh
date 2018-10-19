/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 12:50:00 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 21:52:48 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <termcap.h>

static char	*expand_str(char *s1, char *s2, int index)
{
	char	*start;
	char	*end;

	start = ft_strsub(s1, 0, index);
	end = ft_strsub(s1, index, ft_strlen(s1) - index);
	ft_strdel(&s1);
	s1 = ft_strdup(start);
	s1 = ft_str_joinordup(s1, s2);
	s1 = ft_str_joinordup(s1, end);
	ft_strdel(&start);
	ft_strdel(&end);
	return (s1);
}

int			check_size(t_shell *shell, char *buffer, int len_start)
{
	int		i;
	int		y;
	int		len_line;

	i = 0;
	y = 0;
	len_line = len_start;
	if (!shell->input.buffer || !shell->input.buffer[0] || !buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n' || len_line >= shell->input.nb_co)
		{
			y++;
			len_line = -1;
		}
		len_line++;
		i++;
	}
	return (y);
}

static void	util_paste(t_shell *shell)
{
	put_line(shell->input.buffer);
	shell->input.end_buf.y = shell->input.start.y + calculate_end_buf_y(shell);
	get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
	util_move(shell->input.cursor.x, shell->input.cursor.y);
}

void		paste_copy(t_shell *shell, char *copy_paste)
{
	if (check_size(shell, shell->input.buffer, shell->input.start.x) +
		check_size(shell, copy_paste, 0) >= shell->input.nb_li - 1)
	{
		tputs(tgetstr("bl", NULL), 1, ft_putchar_term);
		return ;
	}
	if (shell->input.len == 0)
	{
		shell->input.buffer = ft_str_joinordup(shell->input.buffer, copy_paste);
		shell->input.len = ft_strlen(shell->input.buffer);
		shell->input.i = shell->input.len;
	}
	else
	{
		shell->input.buffer = expand_str(shell->input.buffer,
			copy_paste, shell->input.i);
		shell->input.len = ft_strlen(shell->input.buffer);
		shell->input.i = shell->input.len;
		util_move(shell->input.start.x, shell->input.start.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
	}
	util_paste(shell);
}
