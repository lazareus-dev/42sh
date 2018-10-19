/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_get_word.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 13:05:58 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 13:06:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

void	reset_buffer(char **buff, char **ptr, char **tmp, int *ret)
{
	*ret = 0;
	while (**buff == ' ')
		(*buff)++;
	*ptr = *buff;
	*tmp = *buff;
}

int		parse_buffer(char *buff, char **ptr)
{
	char	*tmp;
	int		quote;
	int		ret;

	quote = 0;
	reset_buffer(&buff, &tmp, ptr, &ret);
	while (*buff)
	{
		if ((*buff == '"' || *buff == '\'') && !ft_is_quoted(tmp, buff))
			quote = !quote;
		else if (is_operator_ctrl_char(*buff) && !quote)
		{
			buff++;
			reset_buffer(&buff, &tmp, ptr, &ret);
			continue ;
		}
		else if (*buff == ' ' && !quote)
		{
			ret = 1;
			*ptr = buff + 1;
		}
		buff++;
	}
	return (ret);
}

int		quote_parsing(t_input *input)
{
	if (is_quoting_char(input->compl.word[0]))
		input->compl.quoted = is_quoting_char(input->compl.word[0]);
	remove_quoting(&input->compl.word);
	return (0);
}

/*
**	Check if we look for a variable.
**	Check if we are in a path, dissociates path and word to be
**	completed if so.
**	Handle the quoting.
*/

int		parse_word(t_input *input, t_shell *shell)
{
	char *tmp_word;

	tmp_word = NULL;
	if (input->compl.word[0] == '$')
		input->compl.is_var = 1;
	if (ft_strchr(input->compl.word, '/'))
	{
		input->compl.path = ft_get_path(input->compl.word);
		input->compl.path = expand_tilde_regular(input->compl.path, shell);
		tmp_word = ft_strdup(ft_get_last_path_elem(input->compl.word));
		ft_strdel(&input->compl.word);
		input->compl.word = tmp_word;
		if (tmp_word)
			input->compl.word_len = ft_strlen(tmp_word);
		input->compl.is_cmd = 0;
	}
	quote_parsing(input);
	return (0);
}

/*
**	Get the letters ("word") to be completed
*/

int		get_word(t_input *input, t_shell *shell)
{
	char	*buff;
	char	*ptr;

	ptr = NULL;
	buff = ft_strsub(input->buffer, 0, input->i);
	if (input->buffer[input->i])
		input->compl.middleofword = 1;
	if (!parse_buffer(buff, &ptr))
		input->compl.is_cmd = 1;
	input->compl.word = ft_strdup(ptr);
	if (ptr)
		input->compl.word_len = ft_strlen(ptr);
	parse_word(input, shell);
	ft_strdel(&buff);
	return (0);
}
