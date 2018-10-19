/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstrdel.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 18:57:52 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/12 19:00:01 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lststr_del(t_list **head)
{
	t_list	*del;
	t_list	*hook;
	char	*str;

	if (!head)
		return ;
	del = *head;
	while (del)
	{
		hook = del->next;
		str = (char *)del->content;
		ft_strdel(&str);
		free(del);
		del = hook;
	}
	del = NULL;
	head = NULL;
}

void	ft_lstrdel(void *content, size_t content_size)
{
	char	*str;

	str = (char *)content;
	ft_strdel(&str);
	content_size = 0;
}
