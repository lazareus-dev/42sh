/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtab_alloc.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 17:40:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:39:58 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtab_alloc(size_t size)
{
	char	**tab;
	size_t	i;

	if (size <= 1)
		return (NULL);
	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	while (i < size)
	{
		tab[i] = NULL;
		++i;
	}
	return (tab);
}
