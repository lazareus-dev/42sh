/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/03 15:42:56 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 18:32:38 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"
#include <sys/stat.h>

static void	execute_cd(t_cd *cd, t_shell *shell, char *path)
{
	cd->final_pwd = ft_strdup(msh_getenv("PWD", shell));
	if (!cd->final_pwd)
		cd->final_pwd = get_pwd();
	cd->final_oldpwd = cd->final_pwd;
	ft_setenv("OLDPWD", cd->final_oldpwd, &shell->env);
	chdir(path);
	if (cd->lnk_follow == L_OPT)
		cd->final_pwd = ft_strdup(path);
	else
		cd->final_pwd = get_pwd();
	ft_setenv("PWD", cd->final_pwd, &shell->env);
	cd->prev_dir ? ft_putendl(path) : NULL;
}

/*
** Entry point of cd built-in
*/

int			msh_cd(char **args, t_shell *shell)
{
	t_cd	cd;
	char	*path;

	if (init_cd(&cd, args))
		return (1);
	path = resolve_path(&cd, shell);
	if (path == NULL)
		return (1);
	if (access(path, F_OK))
		return (msh_nofile(&path));
	if (!ft_is_dir(path))
		return (msh_notdir(&path));
	if (access(path, X_OK))
		return (msh_noaccess(&path));
	execute_cd(&cd, shell, path);
	ft_strdel(&path);
	clean_cd(&cd);
	return (0);
}
