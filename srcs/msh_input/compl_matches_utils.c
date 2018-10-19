/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_matches_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/13 11:11:46 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/13 11:11:46 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_setunsetenv.h"

void	test_match(char *cmp, t_list **matches, t_compl *compl)
{
	size_t	cmp_len;
	t_list	*node;

	if (ft_strequ(cmp, "..") || ft_strequ(cmp, "."))
		return ;
	if (ft_match(cmp, compl->word))
	{
		cmp_len = ft_strlen(cmp);
		if (!(node = ft_lstnew(cmp, cmp_len + 1)))
			return ;
		ft_lst_insertionsort(matches, node, ft_strcmp_void);
		compl->nb_matches++;
		if (compl->max_match_len < cmp_len)
			compl->max_match_len = cmp_len;
	}
}

void	match_cmd(t_list **matches, t_shell *shell, t_compl *compl)
{
	t_list	*tmp;
	int		i;

	if (!shell->bin_table)
		return ;
	i = -1;
	while (++i < shell->bin_table->size - 1)
	{
		if (shell->bin_table->table[i])
		{
			tmp = shell->bin_table->table[i];
			while (tmp)
			{
				test_match(ft_get_last_path_elem(tmp->content),
					matches, compl);
				tmp = tmp->next;
			}
		}
	}
}

void	match_builtin(t_list **matches, t_compl *compl)
{
	test_match("exit", matches, compl);
	test_match("cd", matches, compl);
	test_match("echo", matches, compl);
	test_match("setenv", matches, compl);
	test_match("unsetenv", matches, compl);
	test_match("env", matches, compl);
	test_match("hash", matches, compl);
	test_match("history", matches, compl);
	test_match("export", matches, compl);
	test_match("unset", matches, compl);
}

void	match_var(t_list **matches, t_headlst varlst, t_compl *compl)
{
	t_var	*env;
	char	*tmp;
	char	*env_name;

	env = varlst.first;
	while (env)
	{
		env_name = get_var_name(env->var);
		tmp = ft_strjoin("$", env_name);
		test_match(tmp, matches, compl);
		ft_strdel(&env_name);
		ft_strdel(&tmp);
		env = env->next;
	}
}
