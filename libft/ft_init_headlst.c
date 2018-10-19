/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_headlst.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 14:38:07 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 14:40:55 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_headlst	*ft_init_headlst(void)
{
	t_headlst *head;

	head = (t_headlst *)malloc(sizeof(t_headlst));
	if (!head)
		return (NULL);
	head->first = NULL;
	head->last = NULL;
	head->nb_node = 0;
	return (head);
}
