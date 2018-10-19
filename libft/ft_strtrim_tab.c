/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim_tab.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/04 23:29:20 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 23:49:12 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtrim_tab(char ***p_to_tab)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = *p_to_tab;
	i = 0;
	while (tab[i])
	{
		tmp = ft_strtrim(tab[i]);
		free(tab[i]);
		tab[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}
