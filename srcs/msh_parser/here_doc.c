/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   here_doc.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 10:31:43 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 10:14:45 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_parser.h"

void	here_doc_escape(char **line)
{
	char	*p;
	int		escape;

	escape = 0;
	p = *line;
	while (*p)
	{
		if (*p == '\\')
		{
			if (*(p + 1) == '\\')
			{
				escape = !escape;
				ft_memmove(p, p + 1, ft_strlen(p));
			}
			else if (*(p + 1) == '\n' && !escape)
				ft_memmove(p, p + 2, ft_strlen(p));
		}
		p++;
	}
}

void	clean_here_doc(t_redir *redir, t_shell *shell)
{
	char	*here_doc;

	here_doc = redir->hdoc.here_doc;
	if (!redir->hdoc.quoted)
	{
		ft_expand_dollar(&here_doc, shell);
		here_doc_escape(&here_doc);
		redir->hdoc.here_doc = here_doc;
	}
}

void	get_here_doc(t_redir *redir, t_shell *shell)
{
	char	*here_doc;
	char	*line;
	char	*delim;

	delim = ft_strdup(redir->hdoc.delimiter);
	delim = append_char(delim, '\n');
	here_doc = NULL;
	while (101)
	{
		ft_strdel(&shell->input.line);
		shell->input.prompt = DLESS;
		reprompt(shell, shell->input.prompt);
		if (input_loop(shell) == EOF || shell->sigint)
			break ;
		line = shell->input.line;
		if (ft_strequ(line, delim))
			break ;
		here_doc = ft_str_joinordup(here_doc, shell->input.line);
	}
	ft_strdel(&shell->input.line);
	ft_strdel(&delim);
	redir->hdoc.here_doc = here_doc;
	if (here_doc)
		clean_here_doc(redir, shell);
}

void	create_here_doc(t_token *tok, t_redir *redir)
{
	t_shell	*shell;
	char	*delimiter;

	if (!(shell = get_shell()))
		return ;
	if (!tok->next || tok->next->type != WORD)
		return ;
	delimiter = ft_strdup(tok->next->token);
	remove_quoting(&delimiter);
	if (!ft_strequ(delimiter, tok->next->token))
		redir->hdoc.quoted = 1;
	redir->hdoc.delimiter = delimiter;
	get_here_doc(redir, shell);
}
