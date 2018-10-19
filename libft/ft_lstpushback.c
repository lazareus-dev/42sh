/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstpushback.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 17:50:39 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 11:34:00 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **lst, t_list *node)
{
	t_list *run;

	if (!(*lst))
		*lst = node;
	else
	{
		run = *lst;
		while (run->next)
			run = run->next;
		run->next = node;
		node->prev = run;
	}
}
