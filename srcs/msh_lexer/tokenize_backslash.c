/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_backslash.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 15:41:04 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 15:41:05 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

char	*get_quoted_char(char *str, int *index)
{
	char	*ret;

	ret = ft_strndup(str + (*index), 2);
	(*index) += 2;
	return (ret);
}

char	*tokenize_backslash(char *str, int *index)
{
	char	*ret;

	ret = NULL;
	if (str[*index + 1] == '\n')
	{
		(*index) += 2;
		return (NULL);
	}
	if (str[*index + 1])
		ret = get_quoted_char(str, index);
	else
	{
		ret = ft_strdup("\\");
		(*index) += 1;
	}
	return (ret);
}
