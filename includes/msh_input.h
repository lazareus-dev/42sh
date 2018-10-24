/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_input.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 13:33:34 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 10:36:34 by vischlum    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_INPUT_H
# define MSH_INPUT_H

# include "minishell.h"

# define CURSOR						0
# define CURRENT_LINE_END_LIMIT		1
# define INIT_COORD					2

# define BACKSPACE					0
# define DELETE						1

/*
**	msh_input.c 4
*/
int		input_loop(t_shell *shell);

/*
**	move_choice.c 5
*/
void	move_choice(t_shell *shell, char *buf);

/*
**	cursor_position.c 5
*/
int		calculate_end_buf_y(t_shell *shell);
void	get_cursor_position(t_shell *shell, short i);

/*
**	input_utils.c 4 + 2(debug)
*/
void	put_line(char *s);
void	util_move(int x, int y);
int		util_make_choice_to_append_history(char **line);

/*
**	history_navigation.c 3
*/
void	history_up(t_shell *shell);
void	history_down(t_shell *shell);

/*
**	cursor_navigation.c 4
*/
void	go_right(t_shell *shell);
void	go_left(t_shell *shell);
void	deplace_cursor(t_shell *shell, char *buf);

/*
**	backspace_delete.c 5
*/
int		nb_chars_between_2_bs_n(t_shell *shell);
void	backspace(t_shell *shell);
void	delete(t_shell *shell);

/*
**	utils_backspace_delete.c 5
*/
int		nb_bs_n(char *buffer);
int		nb_char_after_last_bs_n(t_shell *shell);
void	make_new_buffer(t_shell *shell, short fonction);
void	deplace_cursor_win_size(t_shell *shell);

/*
**	utils_msh_input.c 4
*/
void	prompt_line_continuation(int prompt_type);
void	init_input_compl(t_input *input);
void	init_input(t_input *input);
int		process_input_newline(t_shell *shell);
int		process_input_eof(t_shell *shell);

/*
**	cut_copy.c 5
*/
void	cut_copy_paste(t_shell *shell, char *buf);

/*
**	paste.c 4
*/
int		check_size(t_shell *shell, char *buffer, int len_start);
void	paste_copy(t_shell *shell, char *copy_paste);

/*
**	window_size.c 3
*/
void	window_size();

/*
**	process_input_printable.c 3
*/
int		process_input_printable(char c, t_shell *shell);

/*
**	compl_display_calculate.c
*/
int		rows_and_cols(t_input *input);
void	update_window_several_lines_to_display(t_input *input, int *y);
void	update_window_one_line_to_display(t_input *input, int *y);

/*
**	compl_display.c
*/
int		display_list(t_shell *shell);

/*
**	msh_completion.c
*/
void	msh_completion(t_shell *shell);

/*
**	compl_process_word.c
*/
int		process_word(t_compl *compl);

/*
**	clear_screen.c
*/
void	clear_screen(t_shell *shell);

int		check_line_integrity(t_input *input);
int		reprompt(t_shell *shell, int prompt_type);
int		input_to_history(t_shell *shell);
int		check_for_history_expansion(t_shell *shell);

#endif
