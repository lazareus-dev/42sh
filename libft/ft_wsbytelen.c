/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wcslen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/22 18:50:38 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/22 19:37:35 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wsbytelen(const wchar_t *s)
{
	size_t wslen;
	size_t bytelen;

	bytelen = 0;
	wslen = ft_wcslen(s);
	while (wslen--)
		bytelen += ft_wcbytelen(*s++);
	return (bytelen);
}
