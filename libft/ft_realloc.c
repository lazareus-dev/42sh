/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:29 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 18:52:34 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_realloc(char *s1, char *s2)
{
	char	*tab_out;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab_out = ft_strnew(len);
	if (!tab_out)
		return (NULL);
	if (s1)
	{
		ft_strcpy(tab_out, s1);
		ft_strcat(tab_out, s2);
	}
	ft_strdel(&s1);
	return (tab_out);
}
