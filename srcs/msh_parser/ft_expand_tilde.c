/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_expand_tild.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/18 17:19:13 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/18 17:19:15 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_var_utils.h"

char	*get_home(void)
{
	t_shell *shell;

	shell = get_shell();
	return (msh_getenv("HOME", shell));
}

void	expand_tilde_assignment(char **str)
{
	char	*tilde;
	char	*ptr;
	char	*home;
	size_t	hook;

	home = NULL;
	tilde = *str;
	while ((tilde = ft_strchr(tilde, '~')))
	{
		ptr = tilde;
		if (!ft_ptr_is_quoted(*str, tilde)
			&& (*(tilde - 1) == ':' || *(tilde - 1) == '='))
		{
			home = ft_strdup(get_home());
			hook = ft_expand_str_part(str, tilde, 0, home);
			tilde = *str + hook;
			ft_strdel(&home);
		}
		else
			tilde++;
	}
}

char	*expand_tilde_regular(char *str, t_shell *shell)
{
	char	*parsed;
	char	*home;
	char	*tmp;

	tmp = NULL;
	parsed = NULL;
	if (ft_strcmp(str, "~") == 0)
		parsed = ft_strdup(msh_getenv("HOME", shell));
	else if (ft_strncmp(str, "~/", 2) == 0 ||
		ft_strncmp(str, "~:", 2) == 0)
	{
		tmp = ft_strsub(str, 1, ft_strlen(str) - 1);
		if ((home = msh_getenv("HOME", shell)) != NULL)
		{
			parsed = ft_strjoin(home, tmp);
			ft_strdel(&tmp);
		}
		else
			parsed = tmp;
	}
	else
		parsed = ft_strdup(str);
	ft_strdel(&str);
	return (parsed);
}
