/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 18:27:21 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/21 11:36:57 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"
#include <limits.h>

static void	msh_cd_init_error(char *arg, char *error)
{
	ft_putstr_fd("lsh: cd: ", 2);
	if (!ft_strcmp(error, "invalid option"))
		ft_putstr_fd("-", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

static int	get_opt(char **args, int *i, int *opt)
{
	int		option;

	option = 0;
	while (args[*i] && args[*i][0] == '-' && args[*i][1])
	{
		*opt = 1;
		if (args[*i][*opt] == '-' && args[*i][*opt + 1])
			return (-1);
		if (args[*i][*opt] == '-')
			return (++(*i));
		while (args[*i] && args[*i][*opt])
		{
			if (args[*i][*opt] != 'P' && args[*i][*opt] != 'L')
				return (-1);
			(*opt)++;
		}
		if (args[*i][*opt - 1] == 'P')
			option = P_OPT;
		else
			option = L_OPT;
		(*i)++;
	}
	return (option);
}

int			init_cd(t_cd *cd, char **args, int *i)
{
	int		opt;

	opt = 0;
	cd->lnk_follow = get_opt(args, i, &opt);
	if (cd->lnk_follow == -1)
	{
		msh_cd_init_error(&args[*i][opt], "invalid option");
		msh_cdenverror(USAGE);
		return (1);
	}
	if (ft_strlen(args[*i]) > _POSIX_PATH_MAX)
	{
		msh_cd_init_error(args[*i], "File name too long");
		return (1);
	}
	cd->target = args[*i];
	cd->final_pwd = NULL;
	cd->final_oldpwd = NULL;
	cd->lnk_path = NULL;
	cd->prev_dir = 0;
	return (0);
}

void		clean_cd(t_cd *cd)
{
	ft_strdel(&(cd->final_oldpwd));
	ft_strdel(&(cd->final_pwd));
	ft_strdel(&(cd->lnk_path));
}
