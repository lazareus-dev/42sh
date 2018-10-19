/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_unsetenv.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 15:51:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 17:08:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_var_utils.h"

int			msh_error_identifier(char *id)
{
	ft_putstr_fd("lsh: unset: `", 2);
	ft_putstr_fd(id, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static void	detach_var_node(t_headlst *lst, t_var *del)
{
	t_var *prev;
	t_var *next;

	if (!del)
		return ;
	if ((prev = del->prev))
		prev->next = del->next;
	if ((next = del->next))
		next->prev = del->prev;
	if (lst->first == del)
		lst->first = next;
	if (lst->last == del)
		lst->last = prev;
	ft_strdel(&del->var);
	free(del);
}

int			ft_unsetenv(char *env_name, t_headlst *env)
{
	t_var	*del;

	del = env->first;
	while (del)
	{
		if (check_var_name(del->var, env_name))
		{
			detach_var_node(env, del);
			break ;
		}
		del = del->next;
	}
	if (del == NULL)
		return (1);
	return (0);
}

/*
**	Entry point of unsetenv built-in
*/

int			msh_unsetenv(char **args, t_shell *shell)
{
	int		i;
	int		err;

	if (!args || !*args)
		return (0);
	i = 0;
	err = 0;
	while (args[i])
	{
		if (!ft_is_posixname(args[i]))
		{
			err = msh_error_identifier(args[i++]);
			continue ;
		}
		if (ft_strequ(args[i], "PATH"))
			reset_bintable(0, shell);
		ft_unsetenv(args[i], &shell->env);
		++i;
	}
	return (err);
}
