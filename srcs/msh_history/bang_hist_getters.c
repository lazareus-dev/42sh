/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hist_getters.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/02 15:34:18 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:39:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

char	*get_match_hist_contain(char *needle, t_history *history)
{
	int		i;

	i = history->nb_node;
	while (--i)
	{
		if (ft_strstr(history->hash_hist[i], needle))
			return (history->hash_hist[i]);
	}
	return (NULL);
}

char	*get_match_hist_begin(char *needle, t_history *history)
{
	int		i;
	char	*match;

	i = history->nb_node;
	match = NULL;
	while (i--)
	{
		if (ft_match(history->hash_hist[i], needle))
			match = history->hash_hist[i];
	}
	return (match);
}
