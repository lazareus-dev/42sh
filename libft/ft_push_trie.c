/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_push_trie.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/21 18:14:51 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:49:51 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_trie(t_trie **head, char *str)
{
	t_trie	*node;
	int		index;

	if (!head || !str)
		return ;
	node = *head;
	while (*str)
	{
		index = *str - 'a';
		if (!node->character[index])
			node->character[index] = ft_new_trie();
		node = node->character[index];
		str++;
	}
	node->is_leaf = 1;
}
