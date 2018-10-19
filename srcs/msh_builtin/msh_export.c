/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_export.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:40:48 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 18:41:11 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_hashbin.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"

int		print_exported(char *variable)
{
	char	*ptr;
	size_t	len;

	if (!(ptr = ft_strchr(variable, '=')))
		return (1);
	len = ptr - variable;
	ft_printf("%s %.*s=\"%s\"\n", "export", len, variable, ptr + 1);
	return (0);
}

/*
**	export -p
*/

int		display_exported_var(t_shell *shell)
{
	t_var	*node;

	node = (t_var *)shell->env.first;
	while (node)
	{
		if (node->exported)
			print_exported(node->var);
		node = node->next;
	}
	return (0);
}

/*
**	Moves the node from the local variables list to
**	the environment list
*/

int		export_var(t_var *node, t_shell *shell)
{
	t_var	*prev;
	t_var	*next;

	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (shell->local_var.first == node)
		shell->local_var.first = next;
	if (shell->local_var.last == node)
		shell->local_var.last = prev;
	node->exported = EXPORTED;
	node->prev = NULL;
	node->next = NULL;
	push_back(&shell->env, node);
	shell->local_var.nb_node -= 1;
	shell->env.nb_node += 1;
	return (0);
}

/*
**	Marks any variable as exported, moves it to
**	environment list if from local var list
**	Updates the variable if '=' is in the entry
*/

int		ft_export(char *variable, t_shell *shell)
{
	t_var	*node;
	char	*assignment;

	node = var_exists(variable, shell);
	assignment = ft_strdup(variable);
	if (ft_strchr(variable, '~'))
		expand_tilde_assignment(&assignment);
	if (node == NULL && ft_strchr(variable, '='))
		add_new_var(assignment, &shell->env, EXPORTED);
	else if (node != NULL)
	{
		if (node->exported == PRIVATE)
			export_var(node, shell);
		if (ft_strchr(variable, '='))
			ft_update_var(node, assignment);
		if (!ft_strncmp(node->var, "PATH=", 5))
			reset_bintable(1, shell);
	}
	ft_strdel(&assignment);
	return (0);
}

/*
**	Entry point of export builtin
*/

int		msh_export(char **av, t_shell *shell)
{
	char	**ptr;

	if (!av)
		return (1);
	if (!*av || ft_strequ(av[0], "-p"))
		return (display_exported_var(shell));
	ptr = av;
	while (*ptr)
	{
		ft_export(*ptr, shell);
		ptr++;
	}
	return (0);
}
