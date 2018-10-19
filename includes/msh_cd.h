/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 15:43:44 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 18:31:38 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MSH_CD_H
# define MSH_CD_H

# define L_OPT 0
# define P_OPT 1

typedef struct	s_cd
{
	char		*target;
	char		*final_oldpwd;
	char		*final_pwd;
	char		*lnk_path;
	int			opt;
	int			prev_dir;
	int			lnk_follow;
}				t_cd;

/*
**	msh_cd.c
*/
int				msh_cd(char **args, t_shell *shell);

/*
**	msh_cd_calculate.c
*/
char			*resolve_path(t_cd *cd, t_shell *shell);

/*
**	msh_cd_utils.c
*/
int				init_cd(t_cd *cd, char **args);
void			clean_cd(t_cd *cd);

#endif
