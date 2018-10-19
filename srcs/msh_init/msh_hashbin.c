/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_hashbin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/28 16:26:04 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:44:40 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_parser.h"
#include "../../includes/msh_lstenv.h"
#include "../../includes/msh_var_utils.h"
#include <dirent.h>

static void		fill_bintable(t_hash_table *table, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*value;

	if (!(dir = opendir(path)))
		return ;
	value = NULL;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] == '.')
			continue ;
		value = ft_triplejoin(path, "/", dirent->d_name);
		if (!ft_is_dir(value))
			ft_hash_addbin(table, dirent->d_name, value);
		ft_strdel(&value);
	}
	closedir(dir);
}

static void		create_bintable(t_shell *shell, char **paths, int nb_bin)
{
	int	i;
	int size;

	size = nb_bin * 2;
	shell->bin_table = ft_create_hash_table(size);
	i = 0;
	while (paths && paths[i])
		fill_bintable(shell->bin_table, paths[i++]);
}

static int		count_bin(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*full_path;
	int				nb_bin;

	if (!(dir = opendir(path)))
		return (0);
	full_path = NULL;
	nb_bin = 0;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] == '.')
			continue ;
		full_path = ft_triplejoin(path, "/", dirent->d_name);
		if (!ft_is_dir(full_path))
			nb_bin += 1;
		ft_strdel(&full_path);
	}
	closedir(dir);
	return (nb_bin);
}

int				init_bintable(t_shell *shell)
{
	char			*path_value;
	char			**paths;
	int				nb_bin;
	int				i;

	path_value = msh_getenv("PATH", shell);
	paths = ft_strsplit(path_value, ':');
	i = 0;
	nb_bin = 0;
	while (paths && paths[i])
	{
		if (paths[i][0] == '~')
			paths[i] = expand_tilde_regular(paths[i], shell);
		nb_bin += count_bin(paths[i++]);
	}
	if (nb_bin)
		create_bintable(shell, paths, nb_bin);
	else
		shell->bin_table = NULL;
	shell->nb_binaries = nb_bin;
	ft_matricedel(&paths);
	return (nb_bin);
}

int				reset_bintable(int reinit, t_shell *shell)
{
	if (shell->bin_table)
	{
		ft_free_hashtable(&shell->bin_table);
		shell->bin_table = NULL;
	}
	if (reinit)
		init_bintable(shell);
	return (0);
}
