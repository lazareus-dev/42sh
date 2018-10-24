/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_completion.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 16:07:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 13:53:41 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_completion.h"

#include <termcap.h>
#include <sys/ioctl.h>

static void	insert_completion(t_shell *shell, char *word)
{
	int	i;

	i = shell->input.compl.word_len;
	while (i--)
		backspace(shell);
	paste_copy(shell, word);
}

static int	update_screen(t_shell *shell)
{
	char	buff[BUFFSIZE];

	ft_bzero(buff, BUFFSIZE);
	read(shell->terminal.fd, buff, BUFFSIZE - 1);
	if (buff[0] != 9)
	{
		util_move(shell->input.end_buf.x, shell->input.end_buf.y);
		tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, ft_putchar_term);
		util_move(shell->input.cursor.x, shell->input.cursor.y);
		ioctl(shell->terminal.fd, TIOCSTI, buff);
		return (1);
	}
	return (0);
}

static void	reset_compl(t_compl *compl)
{
	ft_strdel(&compl->word);
	ft_strdel(&compl->closest_match);
	ft_strdel(&compl->path);
	ft_lststr_del(&compl->matches);
	compl->word_len = 0;
	compl->nb_matches = 0;
	compl->is_cmd = 0;
	compl->is_var = 0;
	compl->max_match_len = 1;
	compl->quoted = 0;
	compl->middleofword = 0;
}

/*
**	Check if there is a word to complete, if not, look for all
**	the binaries to be matchable.
**	If the buffer is not empty, get the word to be completed
*/

static int	launch_tab_process(t_shell *shell)
{
	init_input_compl(&shell->input);
	if (!shell->input.buffer || !shell->input.buffer[0])
	{
		shell->input.compl.word = ft_strdup("\0");
		shell->input.compl.is_cmd = 1;
	}
	else if (get_word(&shell->input, shell))
		return (1);
	return (0);
}

void		msh_completion(t_shell *shell)
{
	int		turn;

	turn = 0;
	while (101)
	{
		if (turn == 0)
		{
			if (!launch_tab_process(shell))
			{
				if (!process_word(&shell->input.compl))
				{
					insert_completion(shell, shell->input.compl.closest_match);
					break ;
				}
			}
		}
		else
			display_list(shell);
		++turn;
		if (update_screen(shell))
			break ;
	}
	reset_compl(&shell->input.compl);
}
