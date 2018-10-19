/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_spec.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 11:22:02 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/04 13:01:58 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Check which type it is
*/

int		is_type(char c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
			c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
			c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%' ||
			c == 'b');
}

/*
** Check if there is an arg_size
*/

int		is_arg_size(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' ||
			c == '$' || c == 'L' || c == '\'');
}

/*
** Check if there is an indic
*/

int		is_indic(char c)
{
	return (c == '-' || c == '+' || c == '0' || c == ' ' || c == '#');
}

int		is_known(char c)
{
	return (is_arg_size(c) || is_indic(c) || ft_isdigit(c)
			|| c == '.' || c == '*');
}
