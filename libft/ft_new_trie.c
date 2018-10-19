/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_new_trie.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 18:07:52 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:49:41 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_trie	*ft_new_trie(void)
{
	t_trie	*node;
	int		i;

	node = (t_trie *)malloc(sizeof(t_trie));
	if (!node)
		return (NULL);
	node->is_leaf = 0;
	i = 0;
	while (i < ALPHABET_SIZE)
		node->character[i++] = NULL;
	return (node);
}
