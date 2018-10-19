/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_envpath_from_file.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 13:35:38 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 13:38:02 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

char		*get_envpath_from_file(void)
{
	char	buff[2049];
	char	**paths;
	char	*path;
	int		fd;
	int		i;

	i = 0;
	paths = NULL;
	path = ft_strnew(0);
	if ((fd = open("/etc/paths", O_RDONLY)) > 0)
	{
		ft_bzero(buff, 2049);
		if ((read(fd, buff, 2048)) > 0)
			paths = ft_strsplit(buff, '\n');
		while (paths && paths[i])
			path = ft_triplejoin_free(path, ":", paths[i++]);
		close(fd);
	}
	free(paths);
	return (path);
}
