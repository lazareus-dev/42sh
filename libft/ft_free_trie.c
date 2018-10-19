/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_trie.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/22 10:18:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/22 10:24:43 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_trie(t_trie **head)
{
	t_trie	*del;
	int		index;

	if (!head || !(*head))
		return ;
	del = *head;
	index = 0;
	while (index < ALPHABET_SIZE)
	{
		ft_free_trie(&del->character[index]);
		index++;
	}
	free(del);
	del = NULL;
	head = NULL;
}
