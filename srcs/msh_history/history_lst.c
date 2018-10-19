/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_lst.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 10:54:19 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 10:54:41 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push_back_hist(t_history **head, t_hist *node)
{
	if (!(*head)->first)
		(*head)->first = node;
	else
	{
		(*head)->last->next = node;
		node->prev = (*head)->last;
	}
	(*head)->last = node;
}

t_hist	*new_hist(char *line)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	if (node == NULL)
		return (NULL);
	node->line = ft_strdup(line);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	free_histlst(t_history **head)
{
	t_hist	*hook;
	t_hist	*del;

	if (!head)
		return ;
	del = (*head)->first;
	while (del)
	{
		hook = del->next;
		ft_strdel(&del->line);
		free(del);
		del = hook;
	}
	(*head)->first = NULL;
}

void	free_history(t_history **head)
{
	if (!head)
		return ;
	free_histlst(head);
	if ((*head)->hash_hist)
		free((*head)->hash_hist);
	(*head)->first = NULL;
	(*head)->last = NULL;
	free(*head);
	*head = NULL;
}
