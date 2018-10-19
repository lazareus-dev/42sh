/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stack.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/14 15:34:24 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:50:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_stack	*new_stack(void *content)
{
	t_stack	*node;

	if (!(node = (t_stack*)malloc(sizeof(t_stack))))
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int		stack_is_empty(t_stack *stack)
{
	return (!stack);
}

void	push_stack(t_stack **head, void *content)
{
	t_stack	*node;

	if (!(node = new_stack(content)))
		return ;
	node->next = *head;
	*head = node;
}

void	*pop_stack(t_stack **head)
{
	t_stack	*tmp;
	void	*popped;

	if (stack_is_empty(*head))
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	popped = tmp->content;
	free(tmp);
	return (popped);
}

void	*peek_stack(t_stack *head)
{
	if (stack_is_empty(head))
		return (NULL);
	return (head->content);
}
