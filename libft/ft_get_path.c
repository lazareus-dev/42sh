/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_path.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 10:36:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 10:36:44 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_path(char *str)
{
	char *path;
	char *last_slash;

	if (!(last_slash = ft_strrchr(str, '/')))
		return (NULL);
	path = ft_strsub(str, 0, (last_slash + 1) - str);
	return (path);
}
