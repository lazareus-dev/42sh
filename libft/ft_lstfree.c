/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstfree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/12 18:41:05 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/12 18:43:54 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfree(t_list **alst)
{
	t_list	*hook;

	while (*alst)
	{
		hook = (*alst)->next;
		if ((*alst)->content)
			free((*alst)->content);
		free(*alst);
		*alst = hook;
	}
	*alst = NULL;
}
