/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bang_parser_utils.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:23:12 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:23:13 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

size_t	get_event_needle(char *haystack, t_event *event)
{
	size_t	i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (haystack[i] && haystack[i] != '?'
	&& !is_wd_des(haystack[i])
	&& ft_isprint(haystack[i])
	&& haystack[i] != ' ')
		i++;
	if (i)
		tmp = ft_strsub(haystack, 0, i);
	event->needle = tmp;
	return (i);
}

int		get_event_index(char *nb_start, int *index)
{
	char	*nb;
	size_t	i;

	i = 0;
	*index = 0;
	while (ft_isdigit(nb_start[i]))
		i++;
	nb = ft_strsub(nb_start, 0, i);
	if (!nb)
		*index = -1;
	else
		*index = ft_atoi(nb);
	ft_strdel(&nb);
	return (i);
}
