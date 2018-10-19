/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ptr_is_quoted.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 15:05:11 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 15:05:13 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	is_quoting_char(char c)
{
	if (c == '\'')
		return (S_QUOTE);
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '\\')
		return (BACK_SLASH);
	else
		return (UN_QUOTED);
}

static int	check_quoting(char *str, char *ptr, int escape, int quoted)
{
	int		i;
	int		ret;
	char	c;

	i = 0;
	while ((c = str[i]) && (str + i) != ptr)
	{
		if (c == '\\' && quoted != S_QUOTE)
			escape = !escape;
		else if ((c == '\"' || c == '\'') && !escape)
		{
			if (quoted && quoted == is_quoting_char(c))
				quoted = UN_QUOTED;
			else if (!quoted)
				quoted = is_quoting_char(c);
		}
		if (c != '\\' && quoted != S_QUOTE)
			escape = 0;
		i++;
	}
	ret = quoted ? quoted : escape;
	return (ret);
}

int			ft_ptr_is_quoted(char *str, char *ptr)
{
	int escape;
	int quoted;
	int	ret;

	escape = 0;
	quoted = 0;
	ret = check_quoting(str, ptr, escape, quoted);
	return (ret);
}
