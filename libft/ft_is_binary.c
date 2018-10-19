/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_binary.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/08 14:22:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/08 14:32:48 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_is_binary(char *file)
{
	char	data[1025];
	int		fd;
	int		retread;

	ft_bzero(data, 1025);
	retread = 0;
	if ((fd = open(file, O_RDONLY)) > 0)
	{
		retread = read(fd, data, 1024);
		close(fd);
	}
	return (ft_memchr(data, '\0', retread) != NULL);
}
