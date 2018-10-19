/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strexpand.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 15:52:16 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 16:00:58 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char			*my_strjoin(char const *s1, char const *s2,
		size_t size2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*fresh;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = size2;
	if (!((fresh = (char *)malloc((len1 + len2 + 1) * sizeof(*fresh)))))
		return (NULL);
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			fresh[i] = s1[i];
		else
			fresh[i] = s2[i - len1];
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}

char				*ft_strexpand(char **str, size_t size)
{
	char	*fresh;
	char	*tmp;

	fresh = ft_strnew(size);
	tmp = my_strjoin(*str, fresh, size);
	free(fresh);
	free(*str);
	return (*str = tmp);
}
