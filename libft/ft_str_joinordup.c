/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_joinordup.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 17:13:43 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 17:13:55 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_joinordup(char *s1, char *s2)
{
	char	*tmp;

	if (!s2)
	{
		tmp = ft_strdup(s1);
		free(s1);
		return (tmp);
	}
	if (!s1)
	{
		tmp = ft_strdup(s2);
		return (tmp);
	}
	tmp = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	if (s1)
	{
		ft_strcpy(tmp, s1);
		ft_strcat(tmp, s2);
	}
	free(s1);
	return (tmp);
}
