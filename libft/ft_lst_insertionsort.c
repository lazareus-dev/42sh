/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lst_insertionsort.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 11:35:15 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:49:26 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	insert_node(t_list **entry, t_list *node)
{
	t_list	*node_next;
	t_list	*node_prev;

	if (!entry || !*entry || !node)
		return ;
	node_prev = *entry;
	node_next = (*entry)->next;
	node_prev->next = node;
	if (node_next)
		node_next->prev = node;
	node->next = node_next;
	node->prev = node_prev;
}

void	ft_lst_insertionsort(t_list **head, t_list *node,
		int (*cmp)(void *a, void *b))
{
	t_list	*run;

	if (!head || !node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		run = *head;
		while (run->next && ((*cmp)(node->content, run->next->content) > 0))
			run = run->next;
		insert_node(&run, node);
	}
}
