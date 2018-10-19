/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace_delete_utils.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 13:56:32 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/29 13:56:34 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"

#include <termcap.h>

int			nb_char_after_last_bs_n(t_shell *shell)
{
	char	*buffer;
	int		nb;
	int		len;

	nb = 0;
	len = (int)ft_strlen(shell->input.buffer) - 1;
	buffer = shell->input.buffer;
	while (index > 0)
	{
		if (buffer[len] == '\n')
			break ;
		len--;
		nb++;
	}
	return (nb);
}

static void	print_buffer(t_shell *shell)
{
	util_move(shell->input.start.x, shell->input.start.y);
	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
	put_line(shell->input.buffer);
}

void		make_new_buffer(t_shell *shell, short fonction)
{
	char	*start;
	char	*end;
	char	*tmp;

	tmp = NULL;
	if (fonction == BACKSPACE)
	{
		start = ft_strsub(shell->input.buffer, 0, (shell->input.i - 1));
		end = ft_strsub(shell->input.buffer, shell->input.i,
				(shell->input.len - ft_strlen(start)));
	}
	else
	{
		start = ft_strsub(shell->input.buffer, 0, shell->input.i);
		end = ft_strsub(shell->input.buffer, (shell->input.i + 1),
				(shell->input.len - ft_strlen(start)));
	}
	tmp = ft_str_joinordup(tmp, start);
	tmp = ft_str_joinordup(tmp, end);
	ft_strdel(&start);
	ft_strdel(&end);
	ft_strdel(&shell->input.buffer);
	shell->input.buffer = tmp;
	print_buffer(shell);
}

/*
**	si la line trop > la fenetre,cursor est mis automatique a la fin de la ligne
*/

void		deplace_cursor_win_size(t_shell *shell)
{
	if (shell->input.start.y < 0)
	{
		shell->input.i = shell->input.len;
		shell->input.cursor.x = shell->input.end_buf.x;
		shell->input.cursor.y = shell->input.end_buf.y;
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	}
}
