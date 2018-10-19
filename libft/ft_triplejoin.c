/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_triplejoin.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 14:18:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 14:19:26 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_triplejoin(char *s1, char *s2, char *s3)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	out = ft_realloc(out, s3);
	return (out);
}
