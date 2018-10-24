/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vischlum <vischlum@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 18:36:14 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 11:23:41 by vischlum    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf/ft_printf.h"
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>

# define BUFFSIZE 32

# define SP_CHARS		"!@#^&*-+=~:?./,\n"
# define ESCAPE_CHARS	" \"!@#^&*=~:?/\n"
# define SPECIAL_PARAM	"@*#?-$!0"
# define SP_BACKSLASH	"$`\"\\\n"

# define BOLD	"\e[1m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define RESET	"\e[0m"

# define S_CMD	0

typedef enum		e_optype
{
	NO_OP,
	SEPARATOR,
	LESS,
	GREAT,
	PIPE,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	ANDGREAT,
	AND,
	DSEMI,
	PROMPT
}					t_optype;

typedef enum		e_toktype
{
	WORD,
	IO_NUMBER,
	OPERATOR,
	REDIRECTION,
	NEWLINE
}					t_toktype;

typedef enum		e_quoted
{
	UNQUOTED,
	SQUOTE,
	DQUOTE,
	BACKSLASH
}					t_quoted;

typedef struct		s_heredoc
{
	char			*delimiter;
	short			quoted;
	char			*here_doc;
}					t_heredoc;

typedef struct		s_redir
{
	t_optype		type;
	int				io_nbr;
	int				fd;
	char			*filename;
	t_heredoc		hdoc;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_token
{
	t_toktype		type;
	t_optype		optype;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_tokenlst
{
	t_token			*first;
	t_token			*last;
	int				nb_token;
}					t_tokenlst;

typedef struct		s_cmds
{
	int				type;
	t_tokenlst		tokens;
	t_redir			*redirlst;
	char			**cmd;
	int				nb_words;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}					t_cmds;

typedef struct		s_var
{
	char			*var;
	short			exported;
	struct s_var	*next;
	struct s_var	*prev;
}					t_var;

typedef struct		s_hist
{
	char			*line;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_history
{
	t_hist			*first;
	t_hist			*last;
	t_hist			*current;
	int				nb_node;
	char			**hash_hist;
	int				hash_hist_size;
	int				index_at_startup;
	int				opt;
	char			*opt_offset;
	char			**opt_args;
	char			*last_matchd_word;
}					t_history;

typedef struct		s_erm
{
	int				fd;
	struct termios	termios;
	struct termios	orig_termios;
}					t_erm;

typedef struct		s_compl
{
	char			*word;
	char			*closest_match;
	char			*path;
	t_list			*matches;
	int				nb_matches;
	short			is_cmd;
	short			is_var;
	short			quoted;
	short			middleofword;
	size_t			word_len;
	size_t			max_match_len;
	int				disp_col;
	int				disp_row;
}					t_compl;

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_input
{
	char			*line;
	char			*buffer;
	char			*h_tmp;
	char			*copy_paste;
	short			first_call_history;
	short			print;
	size_t			i;
	size_t			len;
	t_coord			start;
	t_coord			end_buf;
	t_coord			cursor;
	int				nb_li;
	int				nb_co;
	int				len_prompt;
	int				quoted;
	int				escape;
	int				prompt;
	t_compl			compl;
}					t_input;

typedef struct		s_shell
{
	t_input			input;
	t_headlst		env;
	t_headlst		local_var;
	t_erm			terminal;
	t_hash_table	*bin_table;
	t_history		*history;
	t_tokenlst		*tokenlst;
	t_cmds			*cmds;
	short			sigint;
	int				fd_orig[3];
	int				nb_binaries;
	char			*process_name;
	pid_t			last_process_id;
	int				exit;
	int				exit_status;
}					t_shell;

t_shell				*get_shell(void);
int					get_user_input(t_shell *shell);
int					dispatch_cmd(char **av, t_shell *shell, int fork);
int					is_valid_assignment(char *av);
int					msh_local_var(char **av, t_shell *shell);
void				prompt(t_shell *shell);
void				init_environ(t_shell *shell);
int					init_local_var(t_shell *shell);
char				*get_pwd(void);
int					ft_exit_shell(void);

#endif
