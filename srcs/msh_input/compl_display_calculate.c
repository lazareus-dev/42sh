/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_display_calculate.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 13:18:07 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 13:18:23 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <termcap.h>

/*
** Calculate the best ratio rows/columns for the display
*/

int		rows_and_cols(t_input *input)
{
	int	max_len;

	input->compl.disp_row = 0;
	max_len = (input->compl.max_match_len + 2) * input->compl.nb_matches;
	while (max_len > 0)
	{
		max_len -= input->nb_co;
		input->compl.disp_row++;
	}
	if (input->compl.disp_row > input->nb_li - 2)
		return (-1);
	return (0);
}

void	update_window_several_lines_to_display(t_input *input, int *y)
{
	tputs(tgoto(tgetstr("SF", NULL), 0, (input->compl.disp_row + *y) -
		input->nb_li), 1, ft_putchar_term);
	if ((input->compl.disp_row + *y) - input->nb_li > 0)
	{
		input->cursor.y -= (input->compl.disp_row + *y) - input->nb_li;
		input->end_buf.y = input->cursor.y;
		input->start.y = input->cursor.y;
		*y = input->cursor.y + 1;
	}
}

void	update_window_one_line_to_display(t_input *input, int *y)
{
	if (*y == input->nb_li)
	{
		tputs(tgoto(tgetstr("sf", NULL), 0, 1), 1, ft_putchar_term);
		input->cursor.y -= 1;
		input->end_buf.y = input->cursor.y;
		input->start.y = input->cursor.y;
		*y = input->cursor.y + 1;
	}
}
