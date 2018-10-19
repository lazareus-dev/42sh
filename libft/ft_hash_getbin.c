/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_getbin.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 18:19:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:41:06 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_hash_getbin(t_hash_table *hashtable, char *str)
{
	t_list			*list;
	char			*end;
	unsigned int	hashval;

	hashval = ft_jenkins_hash(str, ft_strlen(str));
	hashval /= 2;
	hashval %= hashtable->size;
	list = hashtable->table[hashval];
	while (list)
	{
		end = ft_strrchr((char *)list->content, '/');
		if (!ft_strcmp(str, end + 1))
			return (list);
		list = list->next;
	}
	return (NULL);
}
