/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_lnk.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/01 15:04:34 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:09:07 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/stat.h>

int	ft_is_lnk(char *path)
{
	struct stat filestat;

	if (lstat(path, &(filestat)) == -1)
		return (0);
	return ((filestat.st_mode & S_IFMT) == S_IFLNK);
}
