/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_add.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 19:02:31 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 19:15:14 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_hash_add(t_hash_table *hashtable, char *str)
{
	t_list			*new_list;
	t_list			*current_list;
	unsigned int	hashval;

	hashval = ft_jenkins_hash(str, ft_strlen(str));
	hashval %= hashtable->size;
	current_list = ft_hash_find(hashtable, str);
	if (current_list != NULL)
		return (1);
	if (!(new_list = ft_lstnew(NULL, 0)))
		return (1);
	new_list->content = ft_strdup(str);
	new_list->next = hashtable->table[hashval];
	hashtable->table[hashval] = new_list;
	return (0);
}
