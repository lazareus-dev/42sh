/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_hashtable.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 12:08:03 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 19:11:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_hashtable(t_hash_table **hashtable)
{
	t_list	*list;
	t_list	*del;
	int		i;

	if (!hashtable || !*hashtable)
		return ;
	i = 0;
	while (i < (*hashtable)->size)
	{
		list = (*hashtable)->table[i];
		while (list)
		{
			del = list;
			list = list->next;
			free(del->content);
			free(del);
		}
		i++;
	}
	free((*hashtable)->table);
	free(*hashtable);
}
