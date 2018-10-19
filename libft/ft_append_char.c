/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:29 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/09 14:23:27 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_append_char(char *s1, char c)
{
	char	*tab_out;
	int		i;
	size_t	len;

	len = ft_strlen(s1) + 2;
	tab_out = ft_strnew(len);
	if (!tab_out)
		return (NULL);
	if (s1)
	{
		i = 0;
		ft_strcpy(tab_out, s1);
		while (tab_out[i])
			i++;
		tab_out[i] = c;
	}
	free(s1);
	return (tab_out);
}
