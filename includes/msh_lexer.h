/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_lexer.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 17:41:29 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 18:33:06 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_LEXER_H
# define MSH_LEXER_H

# include "minishell.h"

/*
**	TOOLS_ARGLST.c
*/

t_tokenlst			*init_tokenlst(void);
void				token_push_back(t_tokenlst *head, t_token *node);
void				free_tokenlst(t_tokenlst **head, int static_head);
t_token				*new_token(char *content, int token_type);
void				del_token(t_tokenlst *lst, t_token *del);

/*
** TOOLS_PARSE.c
*/

char				*join_and_free(char *s1, char *s2);
char				*append_char(char *str, char c);
int					is_separator(char c);

void				tokenize(t_tokenlst *head, char *input);
char				*tokenize_regular(char *s, int *i);
char				*tokenize_operator(char *str, int *index);
char				*tokenize_dquote(char *str, int *index);
char				*tokenize_quote(char *str, int *index);
char				*tokenize_backslash(char *str, int *index);
char				*get_quoted_char(char *str, int *index);

/*
**  LEXER_TOOLS.c
*/

int					get_token_type(char *token, char delimiter);
int					get_operator_type(char *token, int toktype);
int					is_operator_char(char c);
int					is_quoting_char(char c);
int					is_redirection(char *token);
int					is_operator(char *token);
int					is_list_operator(char *token);
t_tokenlst			*msh_lexer(t_tokenlst *head, t_shell *shell);
void				skip_whitespaces(char *str, int *index);

#endif
