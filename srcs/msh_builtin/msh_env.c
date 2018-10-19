/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_env.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/02 11:29:52 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 21:04:57 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_builtin.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"

/*
** Duplicate the envlst in order to launch a command with expanded environment
*/

void		lst_dup(t_headlst *original, t_headlst *copy)
{
	t_var		*tmp;
	t_var		*elem;

	tmp = (t_var *)original->first;
	copy->first = NULL;
	while (tmp)
	{
		if (tmp->exported)
		{
			elem = new_env(tmp->var);
			push_back(copy, elem);
		}
		tmp = tmp->next;
	}
}

/*
** env without argument simply prints the current environ
*/

int			print_var(t_headlst *envlst)
{
	t_var	*env;

	env = (t_var *)envlst->first;
	while (env)
	{
		ft_putendl(env->var);
		env = env->next;
	}
	return (0);
}

/*
** Execute the cmd with original environ plus optional env variables
*/

int			env_launcher_add(char **args, t_shell *shell)
{
	t_shell		tmp_shell;
	int			ret;
	int			i;

	lst_dup(&shell->env, &tmp_shell.env);
	lst_dup(&shell->local_var, &tmp_shell.local_var);
	tmp_shell.bin_table = NULL;
	i = 0;
	while (args[i] && is_valid_assignment(args[i]))
	{
		msh_setenv(args[i], &tmp_shell);
		i++;
	}
	args += i;
	if (*args != NULL)
		ret = dispatch_env(args, &tmp_shell, 1);
	else
		ret = print_var(&tmp_shell.env);
	free_envlst(&(tmp_shell.env));
	free_envlst(&(tmp_shell.local_var));
	return (ret);
}

/*
**  Execute the cmd with empty env plus optional env variables
*/

int			env_launcher_new(char **args, t_shell *shell)
{
	t_shell		tmp_shell;
	t_var		*elem;
	int			ret;
	int			i;

	i = 0;
	tmp_shell.env.first = NULL;
	tmp_shell.local_var.first = NULL;
	while (args[++i] && is_valid_assignment(args[i]))
	{
		elem = new_env(args[i]);
		push_back(&tmp_shell.env, elem);
	}
	tmp_shell.bin_table = shell->bin_table;
	args += i;
	if (*args != NULL)
		ret = dispatch_env(args, &tmp_shell, 1);
	else
		ret = print_var(&tmp_shell.env);
	free_envlst(&(tmp_shell.env));
	return (ret);
}

/*
** Entry point of env builtin
*/

int			msh_env(char **args, t_shell *shell)
{
	int			ret;

	if (!args || !args[0])
		return (print_var(&shell->env));
	if (args[0] && ft_strequ(args[0], "-i"))
		ret = env_launcher_new(args, shell);
	else if (args[0] && is_valid_assignment(args[0]))
		ret = env_launcher_add(args, shell);
	else
		ret = dispatch_cmd(args, shell, 1);
	return (ret);
}
