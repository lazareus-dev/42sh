/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_exec.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/08 14:28:21 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/08 14:28:52 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <sys/stat.h>

int		ft_is_exec(char *path)
{
	struct stat filestat;

	return (stat(path, &filestat) == 0 && filestat.st_mode & S_IXUSR);
}
