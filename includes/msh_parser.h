/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_parser.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 11:29:54 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:36:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_PARSER_H
# define MSH_PARSER_H

int		check_syntax(t_tokenlst *head);
t_cmds	*msh_parser(t_tokenlst *tokenlst, t_shell *shell);

/*
** CMDS functions
*/

t_cmds	*new_cmds(void);
void	push_back_cmds(t_cmds **head, t_cmds *node);
void	free_cmds(t_cmds **head);
void	detach_cmds_node(t_cmds *del);

/*
** Expansion functions
*/

void	msh_expand(t_cmds *cmds, t_shell *shell);
void	expand_tilde_dollar(t_token *token, t_shell *shell);
char	*expand_tilde_regular(char *str, t_shell *shell);
void	expand_tilde_assignment(char **str);
int		ft_expand_dollar(char **str, t_shell *shell);
int		ft_remove_quoting(t_tokenlst *head);
int		remove_quoting(char **str);

/*
** Here_doc functions
*/

void	create_here_doc(t_token *tok, t_redir *redir);

/*
** Simple Commands functions
*/

t_cmds	*create_simple_cmd(t_token **tok);

/*
** Redirections functions
*/

int		create_redir(t_cmds *node, t_token *tok);
void	remove_redir_nodes(t_cmds *head);
void	free_redirlst(t_redir **redir);

#endif
