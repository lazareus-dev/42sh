/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_hashbin_utils.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/18 16:40:35 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:49:50 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_hashbin.h"

int		msh_addbin_to_table(char *cmd, char *fullpath)
{
	t_shell		*shell;

	if (!(shell = get_shell()))
		return (1);
	shell->nb_binaries++;
	if (!shell->bin_table
	|| (shell->nb_binaries * 100 / shell->bin_table->size) > 80)
		return (reset_bintable(1, shell));
	ft_hash_addbin(shell->bin_table, cmd, fullpath);
	return (0);
}
