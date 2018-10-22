/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd_calculate.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 17:52:04 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/21 11:26:46 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"
#include <limits.h>

static int	len_cpy(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] && str[i + 1] != '/')
			ret = i;
		i++;
	}
	if (ret == 0)
		ret++;
	return (ret);
}

static void	browse_matrice(char **matrice, char *tmp_path)
{
	int		i;

	i = 0;
	while (matrice[i])
	{
		if (!ft_strcmp(matrice[i], ".."))
		{
			ft_memmove(tmp_path + len_cpy(tmp_path),
				tmp_path + ft_strlen(tmp_path), ft_strlen(tmp_path));
		}
		else
		{
			if (ft_strcmp(matrice[i], "."))
			{
				if (tmp_path[ft_strlen(tmp_path) - 1] != '/')
					ft_memcpy(tmp_path + ft_strlen(tmp_path), "/", 1);
				ft_memcpy(tmp_path + ft_strlen(tmp_path), matrice[i],
					ft_strlen(matrice[i]));
			}
		}
		i++;
	}
}

static char	*calculate_path(t_cd *cd, t_shell *shell, int relative_path)
{
	char	**matrice;
	char	*tmp_path;

	matrice = ft_strsplit(cd->target, '/');
	if (relative_path)
	{
		cd->final_pwd = ft_strdup(msh_getenv("PWD", shell));
		if (!cd->final_pwd)
			cd->final_pwd = get_pwd();
		tmp_path = ft_memalloc(ft_strlen(cd->final_pwd) + ft_strlen(cd->target)
			+ _POSIX_PATH_MAX);
		ft_memcpy(tmp_path, cd->final_pwd, ft_strlen(cd->final_pwd));
		ft_strdel(&(cd->final_pwd));
	}
	else
	{
		tmp_path = ft_memalloc(ft_strlen(cd->final_pwd) + ft_strlen(cd->target)
			+ _POSIX_PATH_MAX);
		ft_memcpy(tmp_path, "/", 1);
	}
	browse_matrice(matrice, tmp_path);
	ft_matricedel(&matrice);
	return (tmp_path);
}

static char	*like_link(t_cd *cd, t_shell *shell)
{
	if (cd->target[0] == '/')
		return (calculate_path(cd, shell, 0));
	else
		return (calculate_path(cd, shell, 1));
}

char		*resolve_path(t_cd *cd, t_shell *shell)
{
	char *path;

	if (cd->target == NULL || !cd->target[0] || !ft_strcmp(cd->target, "--"))
	{
		if ((path = ft_strdup(msh_getenv("HOME", shell))) == NULL)
			return (msh_cdenverror(HOME_NOT_SET));
	}
	else if (ft_strcmp(cd->target, "-") == 0)
	{
		if ((path = ft_strdup(msh_getenv("OLDPWD", shell))) == NULL)
			return (msh_cdenverror(OLDPWD_NOT_SET));
		cd->prev_dir = 1;
	}
	else
	{
		if (cd->lnk_follow == P_OPT)
			path = ft_strdup(cd->target);
		else
			path = like_link(cd, shell);
	}
	return (path);
}
