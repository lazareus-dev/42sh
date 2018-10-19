/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_screen.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 17:49:20 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 20:25:30 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/msh_input.h"
#include <termcap.h>

void	clear_screen(t_shell *shell)
{
	tputs(tgoto(tgetstr("SF", NULL), 0, shell->input.start.y), 1,
		ft_putchar_term);
	ft_putstr_fd("\e[H\e[J", 0);
	shell->input.start.y = 0;
	shell->input.cursor.y = 0;
	shell->input.end_buf.y = calculate_end_buf_y(shell);
	util_move(0, 0);
	prompt(shell);
	get_cursor_position(shell, INIT_COORD);
	put_line(shell->input.buffer);
	get_cursor_position(shell, CURRENT_LINE_END_LIMIT);
	shell->input.i = shell->input.len;
	util_move(shell->input.cursor.x, shell->input.cursor.y);
}
