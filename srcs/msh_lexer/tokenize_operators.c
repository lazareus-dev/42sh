/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_operators.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 15:37:30 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 15:37:31 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_lexer.h"

char			*tokenize_operator(char *str, int *index)
{
	char	tmp_op[4];
	char	*ret;
	int		i;

	ft_bzero(tmp_op, 4);
	i = 1;
	ret = NULL;
	tmp_op[0] = str[(*index)++];
	while (str[*index] && is_operator_char((str[*index])) && i < 3)
	{
		tmp_op[i] = str[*index];
		if (get_token_type(tmp_op, 0) == 0)
		{
			tmp_op[i] = '\0';
			break ;
		}
		++i;
		++(*index);
	}
	ret = ft_strdup(tmp_op);
	return (ret);
}
