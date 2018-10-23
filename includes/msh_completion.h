/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_completion.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 18:11:35 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 18:11:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_COMPLETION_H
# define MSH_COMPLETION_H

# define ALL_REG_FILES				0
# define DIR_ONLY					1

t_list	*get_matches(t_compl *compl);
int		get_word(t_input *input, t_shell *shell);
void	test_match(char *cmp, t_list **matches, t_compl *compl);
void	match_var(t_list **matches, t_headlst varlst, t_compl *compl);
void	match_cmd(t_list **matches, t_shell *shell, t_compl *compl);
void	match_builtin(t_list **matches, t_compl *compl);
char	*process_soft(char **original, t_compl compl);
void	put_suffix(char **output, int suffix, t_compl compl);
int		get_suffix(char *word, t_compl compl);

#endif
