/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_findkv.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 18:54:35 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 17:42:07 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_hash_findkv(t_hash_table *hashtable, char *key, char *val)
{
	t_list			*list;
	unsigned int	hashkey;

	hashkey = ft_jenkins_hash(key, ft_strlen(key));
	hashkey /= 2;
	hashkey %= hashtable->size;
	list = hashtable->table[hashkey];
	while (list)
	{
		if (ft_strcmp(val, (char *)list->content))
			return (list);
		list = list->next;
	}
	return (NULL);
}
