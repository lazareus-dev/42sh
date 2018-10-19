/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_split.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 15:15:19 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 18:48:48 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_terminal.h"

static void		add_to_lst_and_free(t_tokenlst *head, char **token,
	char delimiter)
{
	t_token *node;
	int		token_type;

	token_type = get_token_type(*token, delimiter);
	if ((node = new_token(*token, token_type)))
		token_push_back(head, node);
	ft_strdel(token);
}

static char		*handle_quoting(char *input, int *index)
{
	char	*token;

	token = NULL;
	if (input[*index] == '\'')
		token = join_and_free(token, tokenize_quote(input, index));
	else if (input[*index] == '\"')
		token = join_and_free(token, tokenize_dquote(input, index));
	else if (input[*index] == '\\')
		token = join_and_free(token, tokenize_backslash(input, index));
	return (token);
}

void			tokenize(t_tokenlst *head, char *input)
{
	int				i;
	char			*token;

	if (!input)
		return ;
	i = 0;
	token = NULL;
	while (input[i])
	{
		skip_whitespaces(input, &i);
		if (is_quoting_char(input[i]))
		{
			token = join_and_free(token, handle_quoting(input, &i));
			if (!is_separator(input[i]))
				token = join_and_free(token, tokenize_regular(input, &i));
		}
		else if (is_operator_char(input[i]))
			token = join_and_free(token, tokenize_operator(input, &i));
		else
			token = join_and_free(token, tokenize_regular(input, &i));
		if (token)
			add_to_lst_and_free(head, &token, input[i]);
	}
}

static int		check_tokenlst(t_tokenlst *head)
{
	t_token *token;

	if (!(token = head->last))
		return (0);
	if (token->type == OPERATOR)
	{
		if (token->optype != AND && token->optype != SEPARATOR)
			if (token->prev && token->prev->type == WORD)
				return (token->optype);
	}
	return (0);
}

t_tokenlst		*msh_lexer(t_tokenlst *head, t_shell *shell)
{
	int		read_again;
	int		eof;
	char	*newline;

	tokenize(head, shell->input.line);
	eof = 0;
	ft_strdel(&shell->input.line);
	while ((read_again = check_tokenlst(head)) && !eof && !shell->sigint)
	{
		init_input(&shell->input);
		prompt_line_continuation(read_again);
		if (get_user_input(shell) == EOF)
			eof = 1;
		tokenize(head, shell->input.line);
		ft_strdel(&shell->input.line);
	}
	newline = ft_strdup("\n");
	add_to_lst_and_free(head, &newline, 0);
	return (head);
}
