/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_setenv.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 17:03:24 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 17:08:57 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_var_utils.h"

int			add_new_var_env(char *name, char *value, t_headlst *env)
{
	t_var	*elem;
	char	*environ;

	environ = ft_triplejoin(name, "=", value);
	elem = new_env(environ);
	elem->exported = 1;
	push_back(env, elem);
	ft_strdel(&environ);
	return (0);
}

int			ft_setenv(char *name, char *value, t_headlst *envlst)
{
	char	*env_name;
	t_var	*env;

	env_name = NULL;
	env = envlst->first;
	while (env)
	{
		env_name = get_var_name(env->var);
		if (ft_strcmp(name, env_name) == 0)
		{
			ft_strdel(&(env->var));
			env->var = ft_triplejoin(name, "=", value);
			ft_strdel(&env_name);
			return (0);
		}
		ft_strdel(&env_name);
		env = env->next;
	}
	add_new_var_env(name, value, envlst);
	return (0);
}

/*
**	Entry point of setenv built-in
*/

int			msh_setenv(char *environ, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*var;
	int		ret;

	if (!environ)
		return (msh_env(NULL, shell));
	if (!ft_strchr(environ, '='))
		return (msh_setenverror(shell));
	var = ft_strdup(environ);
	if (ft_strchr(var, '~'))
		expand_tilde_assignment(&var);
	name = get_var_name(var);
	value = get_var_value(var);
	ret = ft_setenv(name, value, &shell->env);
	if (!(ft_strcmp(name, "PATH")))
		reset_bintable(1, shell);
	ft_strdel(&name);
	ft_strdel(&var);
	return (ret);
}
