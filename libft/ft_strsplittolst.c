/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplittolst.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 16:56:07 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 15:24:49 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_wd_len(const char *s, int (*ft)(int c))
{
	int len;

	len = 0;
	while (s[len] && !ft(s[len]))
		len++;
	return (len);
}

t_list		*ft_strsplittolst(char const *s, int (*ft)(int c))
{
	t_list	*head;
	t_list	*elem;
	char	*tmp;
	int		j;

	head = NULL;
	while (*s)
	{
		while (*s && ft(*s))
			s++;
		if (!*s)
			return (head);
		j = 0;
		if (!(tmp = (char *)malloc(sizeof(char) * (ft_wd_len(s, ft) + 1))))
			return (head);
		while (*s && !ft(*s))
			tmp[j++] = *s++;
		tmp[j] = '\0';
		if (!(elem = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
			return (head);
		free(tmp);
		ft_lstpushback(&head, elem);
	}
	return (head);
}
