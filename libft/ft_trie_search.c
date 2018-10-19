/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_trie_search.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 18:25:16 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 18:33:34 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_trie_search(t_trie *head, char *str)
{
	t_trie	*node;
	int		level;
	int		len;
	int		index;

	if (!head)
		return (0);
	node = head;
	len = ft_strlen(str);
	level = 0;
	while (level < len)
	{
		index = str[level] - 'a';
		if (!node->character[index])
			return (0);
		node = node->character[index];
		level++;
	}
	return (node != NULL && node->is_leaf);
}
