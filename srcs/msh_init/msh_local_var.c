/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_local_var.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 11:18:00 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/29 13:51:26 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_var_utils.h"

int			ft_update_var(t_var *node, char *new_value)
{
	ft_strdel(&node->var);
	node->var = ft_strdup(new_value);
	return (0);
}

int			add_new_var(char *var, t_headlst *lst, int exported)
{
	t_var	*elem;

	elem = new_env(var);
	elem->exported = exported;
	push_back(lst, elem);
	lst->nb_node++;
	return (0);
}

static int	ft_set_local_var(char *var, t_shell *shell)
{
	t_var	*node;
	char	*assignment;

	assignment = ft_strdup(var);
	if (ft_strchr(var, '~'))
		expand_tilde_assignment(&assignment);
	if ((node = var_exists(var, shell)))
		ft_update_var(node, assignment);
	else
		add_new_var(assignment, &shell->local_var, PRIVATE);
	if (!ft_strncmp(var, "PATH=", 5))
		reset_bintable(1, shell);
	ft_strdel(&assignment);
	return (0);
}

int			msh_local_var(char **av, t_shell *shell)
{
	char	**ptr;

	if (!av || !*av)
		return (1);
	ptr = av;
	while (*ptr)
	{
		if (!is_valid_assignment(*ptr))
			return (1);
		ft_set_local_var(*ptr, shell);
		ptr++;
	}
	return (0);
}

int			init_local_var(t_shell *shell)
{
	char	*histfile;
	char	*getpwd;

	shell->local_var.first = NULL;
	shell->local_var.last = NULL;
	getpwd = get_pwd();
	histfile = ft_triplejoin("HISTFILE=", getpwd, "/.lsh_history");
	shell->local_var.nb_node = 0;
	ft_set_local_var(histfile, shell);
	ft_strdel(&histfile);
	ft_strdel(&getpwd);
	return (0);
}
