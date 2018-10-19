/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_arglst.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 15:08:45 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:41:07 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

void		del_token(t_tokenlst *lst, t_token *del)
{
	t_token *prev;
	t_token *next;

	if (!del)
		return ;
	if ((prev = del->prev))
		prev->next = del->next;
	if ((next = del->next))
		next->prev = del->prev;
	if (lst->first == del)
		lst->first = next;
	if (lst->last == del)
		lst->last = prev;
	ft_strdel(&del->token);
	free(del);
}

t_token		*new_token(char *content, int token_type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = ft_strdup(content);
	node->type = token_type;
	if (node->type)
		node->optype = get_operator_type(content, token_type);
	else
		node->optype = NO_OP;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void		token_push_back(t_tokenlst *head, t_token *node)
{
	if (!head->first)
	{
		head->first = node;
		head->last = node;
	}
	else
	{
		node->prev = head->last;
		head->last->next = node;
		head->last = node;
	}
	head->nb_token++;
}

t_tokenlst	*init_tokenlst(void)
{
	t_tokenlst	*head;

	if (!(head = (t_tokenlst*)malloc(sizeof(t_tokenlst))))
		return (NULL);
	head->first = NULL;
	head->last = NULL;
	head->nb_token = 0;
	return (head);
}

void		free_tokenlst(t_tokenlst **head, int static_head)
{
	t_token	*node;
	t_token	*tmp;

	node = (*head)->first;
	while (node)
	{
		tmp = node->next;
		ft_strdel(&node->token);
		free(node);
		node = tmp;
	}
	(*head)->first = NULL;
	(*head)->last = NULL;
	if (!static_head)
	{
		free(*head);
		*head = NULL;
	}
}
