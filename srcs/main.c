/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 13:23:24 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 18:05:31 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/msh_exec.h"
#include "../includes/msh_error.h"
#include "../includes/msh_input.h"
#include "../includes/msh_lexer.h"
#include "../includes/msh_parser.h"
#include "../includes/msh_signal.h"
#include "../includes/msh_terminal.h"

static int			msh_error_eof(t_shell *shell)
{
	ft_putstr_fd("lsh: unexpected EOF while looking for matching `", 2);
	if (shell->input.quoted == SQUOTE)
		ft_putchar_fd('\'', 2);
	else if (shell->input.quoted == DQUOTE)
		ft_putchar_fd('"', 2);
	ft_putendl_fd("'", 2);
	return (2);
}

int					get_user_input(t_shell *shell)
{
	int	ret;

	ret = input_loop(shell);
	if (shell->input.line && shell->input.line[0])
	{
		while (check_line_integrity(&shell->input))
		{
			reprompt(shell, shell->input.quoted);
			ret = input_loop(shell);
			if (ret == EOF)
			{
				if (shell->input.quoted == SQUOTE
				|| shell->input.quoted == DQUOTE)
					ret = msh_error_eof(shell);
				break ;
			}
		}
		if (!check_for_history_expansion(shell))
			input_to_history(shell);
		else if (ret != EOF)
			ret = 1;
	}
	return (ret);
}

static t_tokenlst	*get_tokenlst(t_shell *shell)
{
	t_tokenlst	*head;
	int			ret;

	head = NULL;
	init_input(&shell->input);
	ret = get_user_input(shell);
	if (ret == 0 || ret == 2)
	{
		if (shell->input.line && shell->input.line[0])
		{
			head = init_tokenlst();
			head = msh_lexer(head, shell);
		}
	}
	else if (ret == EOF)
		shell->exit = 1;
	else
		shell->exit_status = 1;
	ft_strdel(&shell->input.line);
	ft_strdel(&shell->input.buffer);
	ft_strdel(&shell->input.h_tmp);
	return (head);
}

static void			msh_loop(t_shell *shell)
{
	shell->input.copy_paste = NULL;
	while (shell->exit == 0)
	{
		set_raw_term(shell);
		prompt(shell);
		if (!(shell->tokenlst = get_tokenlst(shell)))
			continue ;
		if (!shell->sigint)
		{
			if ((shell->cmds = msh_parser(shell->tokenlst, shell))
				&& !shell->sigint)
			{
				set_canonical_term(shell);
				exec_all(shell->cmds, shell);
			}
		}
		free_tokenlst(&shell->tokenlst, 0);
		free_cmds(&shell->cmds);
	}
	ft_putendl("exit");
}

int					main(int ac, char **av)
{
	t_shell	*shell;
	int		exit_status;

	(void)ac;
	if (!(shell = get_shell()))
		return (EXIT_FAILURE);
	shell->process_name = av[0];
	sig_handlers();
	msh_loop(shell);
	exit_status = shell->exit_status;
	ft_exit_shell();
	return (exit_status);
}
