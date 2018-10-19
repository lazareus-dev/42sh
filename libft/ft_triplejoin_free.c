/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_triplejoin_free.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/07 18:59:46 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 19:02:58 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_triplejoin_free(char *s1, char *s2, char *s3)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	out = ft_realloc(out, s3);
	ft_strdel(&s1);
	ft_strdel(&s3);
	return (out);
}
