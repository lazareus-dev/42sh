/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_cd_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <vbranco@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 18:27:21 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 15:09:17 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_cd.h"
#include "../../includes/msh_error.h"
#include "../../includes/msh_var_utils.h"
#include "../../includes/msh_setunsetenv.h"

static int	get_opt(char **args)
{
	if (args[0] && args[0][0] == '-')
	{
		if (args[0][1])
		{
			if (args[0][1] == 'P')
				return (P_OPT);
			else if (args[0][1] == 'L')
				return (L_OPT);
			else if (args[0][1] == '-')
				return (L_OPT);
			else
				return (-1);
		}
	}
	return (L_OPT);
}

static char	*get_target(char **args)
{
	if (args[0] && args[0][0] == '-' &&
		(args[0][1] == 'L' || args[0][1] == 'P'))
		return (args[1]);
	else
		return (args[0]);
}

int			init_cd(t_cd *cd, char **args)
{
	cd->lnk_follow = get_opt(args);
	if (cd->lnk_follow == -1)
	{
		ft_putstr_fd("sh: cd: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": invalid option", 2);
		msh_cdenverror(USAGE);
		return (1);
	}
	cd->target = get_target(args);
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
