/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 18:22:33 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/24 18:22:33 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t need_len;
	size_t i;

	need_len = ft_strlen(needle);
	if (need_len == 0)
		return ((char *)haystack);
	while (len != 0 && *haystack)
	{
		i = 0;
		while (i < len && i < need_len && *(haystack + i) == *(needle + i))
			i++;
		if (i == need_len)
			return ((char *)(haystack));
		haystack++;
		len--;
	}
	return (NULL);
}
