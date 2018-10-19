/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_var_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 16:16:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:52:07 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_var_name(char *shell_var, char *new_var)
{
	char	*ptr;
	size_t	len;
	int		ret;

	if ((ptr = ft_strchr(new_var, '=')))
		len = (long)(ptr - new_var);
	else
		len = ft_strlen(new_var);
	ret = (ft_strnequ(shell_var, new_var, len)
		&& (shell_var[len] == '='));
	return (ret);
}

t_var	*var_exists(char *var, t_shell *shell)
{
	t_var	*node;

	node = (t_var *)shell->env.first;
	while (node)
	{
		if (check_var_name(node->var, var))
			return (node);
		node = node->next;
	}
	node = (t_var *)shell->local_var.first;
	while (node)
	{
		if (check_var_name(node->var, var))
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*get_var_name(char *env)
{
	int		i;
	char	*name;

	if (!env)
		return (NULL);
	if ((i = ft_locate_char(env, '=')) == -1)
		return (NULL);
	name = ft_strndup(env, i);
	return (name);
}

/*
**	Return static pointer to environment value
*/

char	*get_var_value(char *env)
{
	int		i;

	if (!env)
		return (NULL);
	if ((i = ft_locate_char(env, '=')) == -1)
		return (NULL);
	return (env + i + 1);
}

char	*msh_getenv(char *name, t_shell *shell)
{
	char	*value;
	t_var	*variable;

	value = NULL;
	if ((variable = var_exists(name, shell)))
		value = get_var_value(variable->var);
	return (value);
}
