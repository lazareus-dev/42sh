/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   msh_echo.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:11:39 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 21:05:04 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_echo(char **msg)
{
	int	newline;
	int	output;

	newline = 0;
	output = 0;
	if (msg[0] != NULL && ft_strequ(msg[0], "-n"))
	{
		msg += 1;
		newline = 1;
	}
	while (*msg)
	{
		if (output)
			ft_putchar(' ');
		ft_putstr(*msg);
		msg++;
		output = 1;
	}
	if (!newline)
		ft_putchar('\n');
	return (0);
}
