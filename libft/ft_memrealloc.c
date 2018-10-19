/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memrealloc.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:28 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 18:29:54 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memrealloc(void *s1, void *s2, size_t size)
{
	char	*tab_out;
	size_t	len;

	len = ft_strlen(s1) + size;
	tab_out = ft_strnew(len);
	if (!tab_out)
		return (NULL);
	if (s1)
	{
		ft_strcpy(tab_out, s1);
		ft_strncat(tab_out, s2, size);
	}
	free(s1);
	return (tab_out);
}
