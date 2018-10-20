/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 14:11:30 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/29 14:11:49 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/msh_lstenv.h"
#include "../includes/msh_history.h"

char		*get_pwd(void)
{
	char cwd[256];
	char *p;

	ft_bzero(cwd, 256);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	else
	{
		p = ft_strdup(cwd);
		return (p);
	}
}

int			is_valid_assignment(char *av)
{
	int	i;

	if (!av)
		return (0);
	if (!ft_strchr(av, '='))
		return (0);
	i = 0;
	if (ft_isdigit(av[0]))
		return (0);
	while (av[i] && av[i] != '=')
	{
		if (!ft_is_posixname_char(av[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	clear_shell(t_shell *shell)
{
	free_envlst(&shell->env);
	free_envlst(&shell->local_var);
	ft_free_hashtable(&(shell->bin_table));
	free_history(&(shell->history));
	ft_strdel(&shell->input.line);
	ft_strdel(&shell->input.buffer);
	ft_strdel(&shell->input.h_tmp);
	ft_strdel(&shell->input.copy_paste);
	close(shell->terminal.fd);
	free(shell);
	return (0);
}

int			ft_exit_shell(void)
{
	t_shell *shell;

	shell = get_shell();
	if (!shell)
		exit(EXIT_FAILURE);
	backup_history(shell);
	clear_shell(shell);
	return (0);
}
