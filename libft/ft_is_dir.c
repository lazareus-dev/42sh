/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_dir.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/02 11:39:21 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 11:40:15 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/stat.h>

int	ft_is_dir(char *path)
{
	struct stat filestat;

	if (stat(path, &(filestat)) == -1)
		return (0);
	return ((filestat.st_mode & S_IFMT) == S_IFDIR);
}
