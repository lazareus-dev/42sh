/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_history.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 17:55:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 11:50:54 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_HISTORY_H
# define MSH_HISTORY_H

# include "minishell.h"

# define INVALID_OPT	0
# define NON_NUM_ARG	1
# define TOO_MANY_OPT	2
# define OUT_OF_RANGE	3
# define REQUIRE_ARG	4
# define TOO_MANY_ARG	5

# define HIST_USAGE1	"history: usage: history [-c] [-d offset] [n] or "
# define HIST_USAGE2 	"history -awrn [filename] or history -ps arg [arg...]"

# define EVENT_NOT_FOUND 1
# define BAD_WD_SPECIF	 2

# define HASH_HIST_MIN	500

# define CONTAIN		0
# define START			1

/*
** History options
*/

typedef enum		e_hopt
{
	HOPT_C = 1,
	HOPT_D = 2,
	HOPT_A = 4,
	HOPT_N = 8,
	HOPT_R = 16,
	HOPT_W = 32,
	HOPT_S = 64,
	HOPT_P = 128
}					t_hopt;

/*
** Event Designators
*/

typedef enum		e_ev_des
{
	NO_DES,
	DASH,
	BANG,
	HASH,
	DOLLAR,
	QUEST_MARK
}					t_ev_des;

/*
** Word Designators
*/

typedef enum		e_wd_des
{
	WD_COLON = 1,
	WD_CARET = 2,
	WD_DOLLAR = 4,
	WD_WILDCARD = 8,
	WD_DASH = 16,
	WD_PERCENT = 32,
	WD_INDEX = 64
}					t_wd_des;

typedef struct		s_event
{
	t_ev_des		ev_des;
	int				index;
	char			*needle;
	char			*hist;
	int				wd_des;
	int				wd_start;
	int				wd_end;
	int				wd_last_arg;
	char			*wd_designator;
	char			*ev_designator;
	char			*expanded_event;
}					t_event;

int					fill_history_from_file(t_history **history,
	char *file, t_shell *shell);
int					add_hist_to_lst(char *line, t_shell *shell);
int					init_history(t_shell *shell);
int					init_hash_hist(t_history **history);
void				free_history(t_history **history);
void				free_histlst(t_history **history);
t_hist				*new_hist(char *line);
void				push_back_hist(t_history **history, t_hist *node);

/*
**	History built-in functions
*/

int					msh_history_error(char **av, int status);
int					history_options(char **av, t_shell *shell);
int					print_history(t_history *history, int start);
int					get_hopt(char **av, t_shell *shell);
int					append_hist_to_file(t_shell *shell);
int					append_latest_to_file(t_shell *shell);
int					append_latest_to_history(t_shell *shell);
int					append_file_to_hist(char *file, t_shell *shell);
int					del_one_hist(t_shell *shell);
int					append_arg_to_hist(t_history *history);
int					print_arg_delete_last(t_history *history);
int					clear_history(t_shell *shell);

/*
**	History expansion functions
*/

int					ft_expand_bang(char **line, t_shell *shell);
char				*get_hist(int index, t_history *history);
char				*get_match_hist_contain(char *needle, t_history *history);
char				*get_match_hist_begin(char *needle, t_history *history);
int					parse_bang(char **bang, t_event *event);
int					is_ev_des(char c);
int					is_wd_des(char c);
void				init_event(t_event *event);
void				clear_event(t_event *event);
int					process_event(t_event *event, char *ptr, t_shell *shell);
int					process_wd_des(t_event *event, t_shell *shell);
int					bang_error(t_event event, int type);
size_t				get_event_needle(char *haystack, t_event *event);
int					get_event_index(char *nb_start, int *index);

#endif
