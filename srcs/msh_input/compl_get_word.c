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

static int	quote_parsing(t_input *input)
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

static int	parse_word(t_input *input, t_shell *shell)
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

static void	parse_token(t_tokenlst *toklst, t_input *input, char *buff)
{
	char	*ptr;
	size_t	buflen;
	int		space;

	space = 0;
	buflen = ft_strlen(buff) - 1;
	ptr = buff + buflen;
	if (buff[buflen] == ' ' && !ft_ptr_is_quoted(buff, ptr))
	{
		space = 1;
		input->compl.word = ft_memalloc(1);
	}
	else
		input->compl.word = ft_strdup(toklst->last->token);
	if (!toklst->first)
		input->compl.is_cmd = 1;
	else if (toklst->first == toklst->last && space == 0)
		input->compl.is_cmd = 1;
	if (toklst->last && toklst->last->prev)
	{
		if ((toklst->last->prev->optype == SEPARATOR && !space)
		|| toklst->last->optype == SEPARATOR)
			input->compl.is_cmd = 1;
	}
}

/*
**	Get the letters ("word") to be completed
*/

int			get_word(t_input *input, t_shell *shell)
{
	char		*buff;
	t_tokenlst	*toklst;

	buff = ft_strsub(input->buffer, 0, input->i);
	if (input->buffer[input->i])
		input->compl.middleofword = 1;
	toklst = init_tokenlst();
	tokenize(toklst, buff);
	parse_token(toklst, input, buff);
	input->compl.word_len = ft_strlen(input->compl.word);
	parse_word(input, shell);
	free_tokenlst(&toklst, 0);
	ft_strdel(&buff);
	return (0);
}
