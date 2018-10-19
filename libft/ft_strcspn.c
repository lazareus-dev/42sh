/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcspn.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 14:44:26 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 15:19:27 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strcspn(const char *s1, const char *reject)
{
	size_t i;
	size_t j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s1[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
