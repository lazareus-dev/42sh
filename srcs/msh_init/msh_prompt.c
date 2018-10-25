/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_prompt.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 17:32:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 18:03:25 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_var_utils.h"

#include <pwd.h>

static char	*get_usr(void)
{
	char			*usr;
	struct passwd	*p;

	usr = NULL;
	if ((usr = getenv("LOGNAME")))
		return (usr);
	p = getpwuid(getuid());
	usr = p->pw_name;
	return (usr);
}

static int	get_path(char *path, t_shell *shell)
{
	char	*pwd;
	char	*ptr;
	int		i;

	i = 0;
	ft_bzero(path, 1025);
	if (!(pwd = ft_strdup(msh_getenv("PWD", shell))))
	{
		if (!(pwd = get_pwd()))
			return (1);
	}
	ptr = ft_get_last_path_elem(pwd);
	if (*ptr == '\0')
		path[i] = '/';
	else
	{
		while (ptr[i])
		{
			path[i] = ptr[i];
			i++;
		}
	}
	ft_strdel(&pwd);
	return (0);
}

void		prompt(t_shell *shell)
{
	char	*usr;
	char	path[1025];

	shell->input.len_prompt = 0;
	usr = get_usr();
	get_path(path, shell);
	write(shell->terminal.fd, BOLD, 4);
	shell->input.len_prompt = ft_strlen(usr);
	ft_putstr(usr);
	write(shell->terminal.fd, "\e[34m", 5);
	ft_putstr("/λση\\");
	shell->input.len_prompt += 5;
	write(shell->terminal.fd, "\e[96m", 5);
	shell->input.len_prompt += ft_strlen(path);
	ft_putstr(path);
	if (!shell->exit_status)
		write(shell->terminal.fd, GREEN, 5);
	else
		write(shell->terminal.fd, RED, 5);
	ft_putstr(" $> ");
	shell->input.len_prompt += 4;
	write(shell->terminal.fd, RESET, 4);
}
