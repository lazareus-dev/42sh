/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 11:51:49 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 12:21:36 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

void	reinit(t_buffer *cur)
{
	if (cur->ptr)
		ft_strdel(&(cur->ptr));
	cur->buf = NULL;
	cur->ptr = NULL;
	cur->fd = 1;
	cur = NULL;
}

int		get_line(t_buffer *cur, char **line)
{
	if (ft_strlen(cur->buf))
	{
		if (!(*line = ft_strndup(cur->buf, cur->start)))
			return (-1);
		cur->buf += cur->start + 1;
		return (1);
	}
	reinit(cur);
	return (0);
}

int		check_input(int const fd, char **line)
{
	char	buf[0];

	if (fd < 0 || line == NULL)
		return (-1);
	if (read(fd, buf, 0) == -1)
		return (-1);
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static t_buffer	cur;
	char			buf[BUFF_SIZE + 1];
	int				retread;

	if ((check_input(fd, line) == -1))
		return (-1);
	if (cur.fd != fd)
		reinit(&cur);
	if (cur.buf == NULL)
	{
		cur.fd = fd;
		if (!(cur.ptr = ft_strnew(BUFF_SIZE)))
			return (-1);
		while ((retread = read(fd, buf, BUFF_SIZE)))
		{
			buf[retread] = '\0';
			cur.ptr = ft_realloc(cur.ptr, buf);
		}
		cur.buf = cur.ptr;
	}
	cur.start = 0;
	while (cur.buf[cur.start] != '\n' && cur.buf[cur.start])
		cur.start++;
	return (get_line(&cur, line));
}
