/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_addbin.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 17:49:21 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 18:00:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_hash_addbin(t_hash_table *hashtable, char *key, char *value)
{
	t_list			*new_list;
	t_list			*current_list;
	unsigned int	hashkey;

	hashkey = ft_jenkins_hash(key, ft_strlen(key));
	hashkey /= 2;
	hashkey %= hashtable->size;
	current_list = ft_hash_getbin(hashtable, key);
	if (current_list != NULL)
		return (1);
	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (1);
	new_list->content = ft_strdup(value);
	new_list->next = hashtable->table[hashkey];
	hashtable->table[hashkey] = new_list;
	return (0);
}
