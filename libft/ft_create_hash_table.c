/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_create_hash_table.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 17:00:52 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:16:59 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_hash_table	*ft_create_hash_table(int size)
{
	t_hash_table	*new_table;
	int				i;

	if (size < 1)
		return (NULL);
	if ((new_table = (t_hash_table *)malloc(sizeof(t_hash_table))) == NULL)
		return (NULL);
	if ((new_table->table = (t_list **)malloc(sizeof(t_list *) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		new_table->table[i++] = NULL;
	new_table->size = size;
	return (new_table);
}
