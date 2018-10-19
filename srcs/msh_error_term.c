/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_error_term.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 16:28:42 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:46:46 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/msh_error.h"

int		term_error(int type)
{
	if (type == TERM_NOT_SET)
	{
		ft_putendl_fd("TERM not set", 2);
		ft_putendl_fd("TERM set to default \"vt100\"", 2);
	}
	else if (type == TERM_ACCESS_DB)
		ft_putendl_fd("Can't access termcap DB", 2);
	else if (type == TERM_NOT_FOUND)
		ft_putendl_fd("Terminal type not defined in DB", 2);
	else if (type == GET_ATTR_FAIL)
	{
		ft_putendl_fd("Cannot get termios struct", 2);
		return (GET_ATTR_FAIL);
	}
	else if (type == 4)
	{
		ft_putendl_fd("STDIN_FIENO is not a valid tty\nexit...", 2);
		return (3);
	}
	else if (type == 5)
	{
		ft_putendl_fd("Cannot open STDIN_FIENO\nexit...", 2);
		return (3);
	}
	return (1);
}
