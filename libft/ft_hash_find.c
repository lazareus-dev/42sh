/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_find.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 18:19:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 19:01:11 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_hash_find(t_hash_table *hashtable, char *str)
{
	t_list			*list;
	unsigned int	hashval;

	hashval = ft_jenkins_hash(str, ft_strlen(str));
	hashval %= hashtable->size;
	list = hashtable->table[hashval];
	while (list)
	{
		if (ft_strcmp(str, (char *)list->content))
			return (list);
		list = list->next;
	}
	return (NULL);
}
