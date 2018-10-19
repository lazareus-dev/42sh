/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_hash.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/18 18:24:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:48:41 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_hashbin.h"

int		print_bintable(t_shell *shell)
{
	t_list			*node;
	t_list			*tmp;
	int				i;

	if (!shell->bin_table)
		return (1);
	i = -1;
	while (++i < shell->bin_table->size)
	{
		node = shell->bin_table->table[i];
		if (node)
		{
			ft_printf("%04d : %s\n", i, node->content);
			tmp = node->next;
			while (tmp)
			{
				if (!tmp->next)
					ft_printf(" └──── %s\n", tmp->content);
				else
					ft_printf(" ├──── %s\n", tmp->content);
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

/*
**	Entry point of hash built-in
**	No argument print the hash_table of binaries
**	-r : Reset the hash_table
*/

int		msh_hash(char **av, t_shell *shell)
{
	if (av && av[0] && ft_strequ(av[0], "-r"))
		reset_bintable(0, shell);
	else
		print_bintable(shell);
	return (0);
}
