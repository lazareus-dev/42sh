/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/02 18:25:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:33:16 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

int		is_ev_des(char c)
{
	if (c == '?')
		return (QUEST_MARK);
	else if (c == '!')
		return (BANG);
	else if (c == '#')
		return (HASH);
	else if (c == '-')
		return (DASH);
	else
		return (0);
}

int		is_wd_des(char c)
{
	if (c == ':')
		return (WD_COLON);
	else if (c == '^')
		return (WD_CARET);
	else if (c == '$')
		return (WD_DOLLAR);
	else if (c == '*')
		return (WD_WILDCARD);
	else if (c == '-')
		return (WD_DASH);
	else if (c == '%')
		return (WD_PERCENT);
	else
		return (0);
}

void	init_event(t_event *event)
{
	event->ev_des = 0;
	event->index = 0;
	event->needle = NULL;
	event->hist = NULL;
	event->wd_des = 0;
	event->wd_start = -1;
	event->wd_end = -1;
	event->wd_last_arg = 0;
	event->wd_designator = NULL;
	event->ev_designator = NULL;
	event->expanded_event = NULL;
}

void	clear_event(t_event *event)
{
	if (event)
	{
		ft_strdel(&(event->needle));
		ft_strdel(&(event->wd_designator));
		ft_strdel(&(event->ev_designator));
		ft_strdel(&(event->expanded_event));
	}
}
