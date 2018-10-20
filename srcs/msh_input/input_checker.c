/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_checker.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 13:03:19 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 18:13:07 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_history.h"
#include <sys/ioctl.h>

int		check_line_integrity(t_input *input)
{
	int		i;
	int		ret;
	char	c;

	input->escape = 0;
	input->quoted = 0;
	i = 0;
	while ((c = input->line[i]) && input->line[i + 1])
	{
		if (c == '\\' && input->quoted != SQUOTE)
			input->escape = !input->escape;
		else if ((c == '\"' || c == '\'') && !input->escape)
		{
			if (input->quoted && input->quoted == is_quoting_char(c))
				input->quoted = UNQUOTED;
			else if (!input->quoted)
				input->quoted = is_quoting_char(c);
		}
		if (c != '\\' && input->quoted != SQUOTE)
			input->escape = 0;
		i++;
	}
	ret = input->quoted ? input->quoted : input->escape;
	return (ret);
}

void	prompt_line_continuation(int prompt_type)
{
	if (prompt_type == SQUOTE)
		write(1, "squote> ", 8);
	else if (prompt_type == DQUOTE)
		write(1, "dquote> ", 8);
	else if (prompt_type == 0)
		write(1, "backsl> ", 8);
	else if (prompt_type == PIPE)
		write(1, "_pipe_> ", 8);
	else if (prompt_type == AND_IF)
		write(1, "cmdand> ", 8);
	else if (prompt_type == OR_IF)
		write(1, "_cmdor> ", 8);
	else if (prompt_type == DLESS)
		write(1, "_h_doc> ", 8);
}

int		reprompt(t_shell *shell, int prompt_type)
{
	if (shell->input.cursor.x == 0)
		util_move(shell->input.cursor.x, shell->input.cursor.y);
	prompt_line_continuation(prompt_type);
	return (0);
}

void	init_input_compl(t_input *input)
{
	input->compl.word = NULL;
	input->compl.closest_match = NULL;
	input->compl.path = NULL;
	input->compl.matches = NULL;
	input->compl.nb_matches = 0;
	input->compl.is_cmd = 0;
	input->compl.is_var = 0;
	input->compl.max_match_len = 1;
	input->compl.quoted = 0;
	input->compl.middleofword = 0;
}

void	init_input(t_input *input)
{
	struct winsize	wind;

	ioctl(0, TIOCGWINSZ, &wind);
	input->nb_li = wind.ws_row;
	input->nb_co = wind.ws_col - 1;
	input->line = NULL;
	input->buffer = NULL;
	input->h_tmp = NULL;
	input->first_call_history = 1;
	input->print = 0;
	input->len = 0;
	input->i = 0;
	init_input_compl(input);
	input->quoted = UNQUOTED;
	input->escape = UNQUOTED;
}
