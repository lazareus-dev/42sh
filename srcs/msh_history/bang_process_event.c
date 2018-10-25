/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_event.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/04 17:12:36 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 16:36:37 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/msh_lexer.h"
#include "../../includes/msh_history.h"

char	*get_nth_token(int index, t_tokenlst *head)
{
	t_token	*node;
	int		i;

	i = 0;
	node = head->first;
	while (i++ < index && node)
		node = node->next;
	if (node)
		return (ft_strdup(node->token));
	return (0);
}

int		process_event_without_range(t_event *event, t_tokenlst *head)
{
	int			ret;

	ret = 0;
	if (event->wd_des & WD_DOLLAR)
		event->wd_start = head->nb_token - 1;
	if (event->wd_start > head->nb_token - 1)
		ret = (BAD_WD_SPECIF);
	else
		event->expanded_event = get_nth_token(event->wd_start, head);
	return (ret);
}

int		process_event_with_range(t_event *event, t_tokenlst *head)
{
	int			i;
	int			end;

	if (event->wd_des & WD_DOLLAR)
		event->wd_last_arg = 1;
	if (event->wd_des & WD_CARET)
		event->wd_start = 1;
	i = event->wd_start;
	end = event->wd_last_arg ? head->nb_token - 1 : event->wd_end;
	if (end == -1)
		end = head->nb_token - 2;
	if (end < i || end > head->nb_token)
		return (BAD_WD_SPECIF);
	while (i <= end)
	{
		event->expanded_event = join_and_free(event->expanded_event,
		get_nth_token(i++, head));
		if (i - 1 != end)
			event->expanded_event = append_char(event->expanded_event, ' ');
	}
	return (0);
}

int		process_wd_des(t_event *event, t_shell *shell)
{
	t_tokenlst	*tokenlst;
	int			ret;

	(void)shell;
	if (!(event->wd_des & WD_INDEX))
	{
		event->expanded_event = ft_strdup(event->hist);
		return (0);
	}
	ret = 0;
	tokenlst = init_tokenlst();
	tokenize(tokenlst, event->hist);
	if (!(event->wd_des & WD_DASH))
		ret = process_event_without_range(event, tokenlst);
	else
		ret = process_event_with_range(event, tokenlst);
	free_tokenlst(&tokenlst, 0);
	return (ret);
}

int		process_event(t_event *event, char *ptr, t_shell *shell)
{
	t_history *history;

	history = shell->history;
	if (event->ev_des == BANG)
		event->index = history->nb_node;
	else if (event->ev_des == DASH)
		event->index = history->nb_node - event->index;
	if (event->ev_des == QUEST_MARK)
		event->hist = get_match_hist_contain(event->needle, history);
	else if (event->ev_des == HASH)
		event->hist = ft_strsub(shell->input.line, 0,
		(ptr - shell->input.line));
	else if (event->needle)
		event->hist = get_match_hist_begin(event->needle, history);
	else
		event->hist = get_hist(event->index - 1, history);
	if (!event->hist)
		return (1);
	return (0);
}
