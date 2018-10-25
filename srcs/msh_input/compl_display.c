/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sel_display.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/25 14:35:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 13:19:47 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_input.h"

#include <termcap.h>

static int	disp_room_error(t_shell *shell)
{
	if (shell->input.cursor.y + 1 == shell->input.nb_li)
	{
		tputs(tgoto(tgetstr("sf", NULL), 0, 1), 1, ft_putchar_term);
		shell->input.cursor.y--;
		shell->input.end_buf.y = shell->input.cursor.y;
		shell->input.start.y = shell->input.cursor.y;
	}
	util_move(0, shell->input.cursor.y + 1);
	ft_putstr_fd("Not enough room to display all ", 2);
	ft_putnbr_fd(shell->input.compl.nb_matches, 2);
	ft_putstr_fd(" results", 2);
	util_move(shell->input.cursor.x, shell->input.cursor.y);
	return (1);
}

static void	put_elem(char *str, int type)
{
	if (type == 1)
		ft_putstr_fd(GREEN, 0);
	else if (type == 2)
		ft_putstr_fd("\e[34m", 0);
	else if (type == 3)
		ft_putstr_fd(RED, 0);
	ft_putstr_fd(BOLD, 0);
	ft_putstr_fd(str, 0);
	if (type == 1)
		ft_putchar_fd('/', 0);
	ft_putstr_fd(RESET, 0);
}

static int	sel_dispatch(char *str, int x, int y, t_compl compl)
{
	char	*tmp_file;
	int		type;

	tmp_file = ft_triplejoin(compl.path, "/", str);
	if (ft_is_lnk(tmp_file))
		type = 2;
	else if (ft_is_dir(tmp_file))
		type = 1;
	else if (ft_is_exec(tmp_file))
		type = 3;
	else
		type = 0;
	util_move(x, y);
	put_elem(str, type);
	ft_strdel(&tmp_file);
	return (0);
}

static void	display_node(t_input *input, t_list *node, int *x, int *y)
{
	if (input->compl.disp_row)
	{
		sel_dispatch(node->content, *x, (*y)++, input->compl);
		if (*y - (input->cursor.y + 1) == input->compl.disp_row)
		{
			*y = input->cursor.y + 1;
			*x += input->compl.max_match_len + 2;
		}
	}
	else
	{
		update_window_one_line_to_display(input, y);
		sel_dispatch(node->content, *x, *y, input->compl);
		*x += input->compl.max_match_len + 2;
	}
}

int			display_list(t_shell *shell)
{
	t_list		*node;
	int			y;
	int			x;
	t_input		*input;

	input = &(shell->input);
	x = 0;
	y = input->cursor.y + 1;
	node = input->compl.matches;
	if (rows_and_cols(input))
		return (disp_room_error(shell));
	update_window_several_lines_to_display(input, &y);
	while (node)
	{
		display_node(input, node, &x, &y);
		node = node->next;
	}
	util_move(input->cursor.x, input->cursor.y);
	return (0);
}
