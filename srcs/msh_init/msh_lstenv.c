/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_lstenv.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 16:55:12 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 11:06:38 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_var_utils.h"

t_var	*new_env(char *environ)
{
	t_var	*elem;

	if (!environ)
		return (NULL);
	elem = (t_var *)malloc(sizeof(t_var));
	if (!elem)
		return (NULL);
	elem->var = ft_strdup(environ);
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	push_back(t_headlst *lst, t_var *elem)
{
	t_var	*run;

	if (!lst)
		return ;
	if (lst->first == NULL)
	{
		lst->first = elem;
		lst->last = elem;
	}
	else
	{
		run = (t_var *)lst->last;
		run->next = elem;
		lst->last = elem;
		elem->prev = run;
	}
}

/*
** Rebuild the environ from linked-list model
** to char** model (usefull with execve and ft_getenv)
*/

char	**lst_to_env(t_headlst *lst)
{
	int		nbelem;
	int		i;
	char	**tab_env;
	t_var	*elem;

	nbelem = 0;
	elem = (t_var *)lst->first;
	while (elem)
	{
		++nbelem;
		elem = elem->next;
	}
	if (!(tab_env = (char **)malloc(sizeof(char *) * (nbelem + 1))))
		return (NULL);
	tab_env[nbelem] = NULL;
	i = 0;
	elem = (t_var *)lst->first;
	while (elem)
	{
		tab_env[i++] = ft_strdup(elem->var);
		elem = elem->next;
	}
	return (tab_env);
}

void	free_envlst(t_headlst *lst)
{
	t_var *hook;
	t_var *del;

	if (!lst)
		return ;
	del = (t_var *)lst->first;
	while (del)
	{
		hook = del->next;
		ft_strdel(&del->var);
		free(del);
		del = hook;
	}
}
