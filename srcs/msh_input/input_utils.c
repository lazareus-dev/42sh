/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/12 16:25:25 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/14 15:20:34 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include "../../includes/msh_history.h"
#include <termcap.h>

void	put_line(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(1, s, len);
}

void	util_move(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar_term);
}

int		check_for_history_expansion(t_shell *shell)
{
	int		ret;

	if (!shell->input.line)
		return (0);
	if (ft_strchr(shell->input.line, '!'))
	{
		ret = ft_expand_bang(&shell->input.line, shell);
		if (ret == 1 || ret == 2 || ret == 6)
			return (1);
		else if (ret == 0)
			ft_putstr(shell->input.line);
	}
	return (0);
}

int		input_to_history(t_shell *shell)
{
	char	*tmp;
	char	*line;

	line = shell->input.line;
	if (!line || !line[0])
		return (1);
	if (ft_strequ(line, "\0") || ft_strequ(line, "\n"))
		return (1);
	tmp = ft_strdup(line);
	tmp[ft_strlen(tmp) - 1] = '\0';
	add_hist_to_lst(tmp, shell);
	ft_strdel(&tmp);
	return (0);
}
