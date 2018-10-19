/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_fd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 12:25:12 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 12:25:28 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int		ft_get_fd_write(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int		ft_get_fd_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}
