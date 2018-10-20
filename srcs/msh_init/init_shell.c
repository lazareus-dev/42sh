/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_art.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 18:31:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 17:18:50 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_history.h"
#include "../../includes/msh_terminal.h"

void	print_shell_header(void)
{
	ft_putstr_fd("\e[H\e[J", 0);
	ft_putstr_fd("\e[1m\e[96m", 0);
	ft_putendl("██╗      █████╗ ███████╗██╗   ██╗");
	ft_putendl("██║     ██╔══██╗╚══███╔╝╚██╗ ██╔╝");
	ft_putendl("██║     ███████║  ███╔╝  ╚████╔╝");
	ft_putendl("██║     ██╔══██║ ███╔╝    ╚██╔╝");
	ft_putendl("███████╗██║  ██║███████╗   ██║");
	ft_putendl("╚══════╝╚═╝  ╚═╝╚══════╝   ╚═╝");
	ft_putstr_fd(BOLD, 0);
	ft_putstr_fd("\e[34m", 0);
	ft_putendl("███████╗██╗  ██╗███████╗██╗     ██╗      ");
	ft_putendl("██╔════╝██║  ██║██╔════╝██║     ██║      ");
	ft_putendl("███████╗███████║█████╗  ██║     ██║      ");
	ft_putendl("╚════██║██╔══██║██╔══╝  ██║     ██║      ");
	ft_putendl("███████║██║  ██║███████╗███████╗███████╗ ");
	ft_putendl("╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ");
	ft_putendl_fd("\e[0m", 0);
}

void	init_shell_var(t_shell *shell)
{
	shell->exit_status = 0;
	shell->exit = 0;
	shell->bin_table = NULL;
	shell->history = NULL;
	shell->tokenlst = NULL;
	shell->cmds = NULL;
	shell->sigint = 0;
	shell->fd_orig[0] = 0;
	shell->fd_orig[1] = 1;
	shell->fd_orig[2] = 2;
}

t_shell	*init_shell(void)
{
	t_shell *shell;

	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (NULL);
	init_shell_var(shell);
	init_input(&shell->input);
	init_environ(shell);
	init_local_var(shell);
	init_bintable(shell);
	init_history(shell);
	if (init_termios(shell) == 3)
		shell->exit = 1;
	if (!shell->exit)
		print_shell_header();
	return (shell);
}

/*
** Get or create the GOD SHELL VARIABLE
*/

t_shell	*get_shell(void)
{
	static t_shell	*shell;

	if (!shell)
		if (!(shell = init_shell()))
			return (NULL);
	return (shell);
}
