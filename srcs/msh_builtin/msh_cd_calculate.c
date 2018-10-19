/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd_calculate.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 17:52:04 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 15:08:45 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"

static int	len_cpy(char *str)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			ret = i;
		i++;
	}
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
				tmp_path + len_cpy(tmp_path) + len_cpy(tmp_path),
				len_cpy(tmp_path));
		}
		else
		{
			if (ft_strcmp(matrice[i], "."))
			{
				ft_memcpy(tmp_path + ft_strlen(tmp_path), "/", 1);
				ft_memcpy(tmp_path + ft_strlen(tmp_path), matrice[i],
					ft_strlen(matrice[i]));
			}
		}
		i++;
	}
}

static char	*calculate_path(t_cd *cd, t_shell *shell)
{
	char	**matrice;
	char	*tmp_path;

	matrice = ft_strsplit(cd->target, '/');
	tmp_path = ft_memalloc(2048);
	cd->final_pwd = ft_strdup(msh_getenv("PWD", shell));
	if (!cd->final_pwd)
		cd->final_pwd = get_pwd();
	ft_memcpy(tmp_path, cd->final_pwd, ft_strlen(cd->final_pwd));
	ft_strdel(&(cd->final_pwd));
	browse_matrice(matrice, tmp_path);
	ft_matricedel(&matrice);
	return (tmp_path);
}

static char	*like_link(t_cd *cd, t_shell *shell)
{
	if (cd->target[0] == '/')
	{
		if (cd->target[1] == '.')
			return (ft_strdup("/"));
		else
			return (ft_strdup(cd->target));
	}
	else
		return (calculate_path(cd, shell));
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
