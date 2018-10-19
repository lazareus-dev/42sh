/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jenkins_hash.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/26 16:13:46 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:53:56 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_jenkins_hash(char *key, size_t len)
{
	size_t	i;
	int		hash;

	hash = 0;
	i = 0;
	while (i != len)
	{
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return ((unsigned int)ft_abs(hash));
}
