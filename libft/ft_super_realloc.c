/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_super_realloc.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 19:49:31 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 11:04:23 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_super_realloc(char *s1, char *s2)
{
	char	*tab_out;
	size_t	len;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
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
	ft_strdel(&s2);
	return (tab_out);
}
