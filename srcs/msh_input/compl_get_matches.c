/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_get_matches.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 18:14:15 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 18:14:17 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_completion.h"

#include <dirent.h>

static t_list	*get_reg_matches(t_compl *compl, int only_dirs)
{
	t_list			*matches;
	struct dirent	*dirent;
	DIR				*dir;

	if (!compl->path)
		compl->path = get_pwd();
	if (!(dir = opendir(compl->path)))
		return (NULL);
	matches = NULL;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (only_dirs == DIR_ONLY)
			if (!ft_is_dir(dirent->d_name))
				continue ;
		test_match(dirent->d_name, &matches, compl);
	}
	closedir(dir);
	return (matches);
}

static t_list	*get_cmd_matches(t_compl *compl, t_shell *shell)
{
	t_list	*matches;

	matches = NULL;
	match_cmd(&matches, shell, compl);
	match_builtin(&matches, compl);
	return (matches);
}

static t_list	*get_var_matches(t_compl *compl, t_shell *shell)
{
	t_list	*matches;

	matches = NULL;
	match_var(&matches, shell->env, compl);
	match_var(&matches, shell->local_var, compl);
	return (matches);
}

t_list			*get_matches(t_compl *compl)
{
	t_shell	*shell;
	t_list	*matches;

	if (!(shell = get_shell()))
		return (NULL);
	if (compl->is_var)
		matches = get_var_matches(compl, shell);
	else if (compl->is_cmd)
	{
		matches = get_cmd_matches(compl, shell);
		if (!matches)
			matches = get_reg_matches(compl, DIR_ONLY);
	}
	else
		matches = get_reg_matches(compl, ALL_REG_FILES);
	return (matches);
}
