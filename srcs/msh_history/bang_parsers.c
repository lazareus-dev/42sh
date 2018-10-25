/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bang_parsers.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:15:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:15:56 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_history.h"

int		wd_error(char c, int type)
{
	ft_putstr_fd("lsh: ", 2);
	if (type == NOT_MODIFIER)
	{
		ft_putchar_fd(c, 2);
		ft_putstr_fd(": ", 2);
	}
	return (type);
}

void	parse_wd_begin(char **bang, t_event *event)
{
	if (ft_isdigit(**bang))
		(*bang) += get_event_index(*bang, &event->wd_start);
	else if (**bang != '-')
	{
		if (**bang == '^')
		{
			event->wd_start = 1;
			event->wd_des |= WD_CARET;
		}
		else if (**bang == '$')
			event->wd_des |= WD_DOLLAR;
		else if (**bang == '*')
		{
			event->wd_start = 1;
			event->wd_des |= (WD_WILDCARD | WD_DASH | WD_DOLLAR);
		}
		(*bang)++;
	}
	else if (**bang == '-')
		event->wd_start = 0;
}

void	parse_wd_end(char **bang, t_event *event)
{
	if (event->wd_des & WD_DOLLAR || event->wd_des & WD_WILDCARD)
		return ;
	if (**bang == '-')
	{
		event->wd_des |= WD_DASH;
		(*bang)++;
		event->wd_last_arg = (**bang == '\n') ? 0 : event->wd_last_arg;
		if (ft_isdigit(**bang))
		{
			get_event_index(*bang, &event->wd_end);
			
			(*bang) += ft_nbr_len(event->wd_start);
		}
	}
	if (**bang == '^')
	{
		event->wd_des |= WD_DASH;
		event->wd_end = 1;
		(*bang)++;
	}
	if (**bang == '$')
	{
		event->wd_last_arg = 1;
		(*bang)++;
	}
}

int		parse_wd_des(char **bang, t_event *event)
{
	char	*beginning;
	char	*end;

	if (!is_wd_des(**bang))
		return (0);
	if (**bang == ':')
		(*bang)++;
	if (!is_wd_des(**bang) && !ft_isdigit(**bang))
		return (NOT_MODIFIER);
	if ((*(*bang - 1)) == ':')
		beginning = *bang - 1;
	else
		beginning = *bang;
	if (**bang == '$')
		event->ev_des = BANG;
	event->wd_des |= WD_INDEX;
	parse_wd_begin(bang, event);
	parse_wd_end(bang, event);
	end = *bang;
	event->wd_designator = ft_strndup(beginning, (end - beginning));
	return (0);
}

int		parse_bang(char **bang, t_event *event)
{
	char	*beginning;
	char	*end;
	int		ret;

	beginning = *bang - 1;
	if ((event->ev_des = is_ev_des(**bang)))
		(*bang)++;
	if (event->ev_des == BANG && !is_wd_des(**bang))
		return (0);
	if (event->ev_des == QUEST_MARK || ft_isalpha(**bang))
		(*bang) += get_event_needle(*bang, event);
	if (event->ev_des == DASH || ft_isdigit(**bang))
		(*bang) += get_event_index(*bang, &event->index);
	end = *bang;
	event->ev_designator = ft_strndup(beginning, (end - beginning));
	ret = parse_wd_des(bang, event);
	return (ret);
}
