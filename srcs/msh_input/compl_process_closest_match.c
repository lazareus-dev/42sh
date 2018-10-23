/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compl_process_closest_match.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/13 10:13:36 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/13 10:13:38 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_sp_chars_in_str(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (ft_strchr(ESCAPE_CHARS, *str))
			count++;
		str++;
	}
	return (count);
}

static void	copy_and_escape(char *dest, char *src, size_t j)
{
	size_t	i;
	size_t	src_len;
	int		escape;

	i = 0;
	src_len = ft_strlen(src);
	escape = 0;
	while (i < src_len)
	{
		if (ft_strchr(ESCAPE_CHARS, src[i]) && !escape)
		{
			dest[j] = '\\';
			escape = 1;
		}
		else
		{
			dest[j] = src[i];
			i++;
			escape = 0;
		}
		j++;
	}
}

static int	get_suffix(char *word, t_compl compl)
{
	char	*tmp_file;
	int		ret;

	tmp_file = NULL;
	ret = 0;
	if (compl.path)
	{
		tmp_file = ft_triplejoin(compl.path, "/", word);
		if (ft_is_dir(tmp_file))
			ret = 1;
		ft_strdel(&tmp_file);
	}
	else
	{
		if (ft_is_dir(word))
			ret = 1;
	}
	return (ret);
}

static void	put_suffix(char **output, int suffix, t_compl compl)
{
	if (suffix == 1)
		ft_strcat(*output, "/");
	else
	{
		if (compl.quoted == DQUOTE)
			ft_strcat(*output, "\"");
		else if (compl.quoted == SQUOTE)
			ft_strcat(*output, "\'");
		if (!compl.middleofword)
			ft_strcat(*output, " ");
	}
}

void		process_soft(char **output, char **original, t_compl compl)
{
	size_t	len_output;

	len_output = ft_strlen(*original) + 2 + (compl.quoted != 0);
	if (!compl.quoted && !ft_strcspn(ESCAPE_CHARS, *original))
	{
		len_output += count_sp_chars_in_str(*original);
		*output = ft_strnew(len_output);
		copy_and_escape(*output, *original, (compl.quoted != 0));
	}
	else
	{
		*output = ft_strnew(len_output);
		if (compl.quoted)
			ft_strcpy((*output) + 1, *original);
		else
			ft_strcpy(*output, *original);
	}
}

/*
**	Add quoting, escaping, last space if file or last slash if dir
*/

void		process_closest_match(char **original, t_compl compl, int full)
{
	char	*output;
	int		suffix;

	process_soft(&output, original, compl);	
	if (full)
	{
		compl.quoted == 2 ? output[0] = '\"' : 0;
		compl.quoted == 1 ? output[0] = '\'' : 0;
		suffix = get_suffix(*original, compl);
		put_suffix(&output, suffix, compl);
	}
	ft_strdel(original);
	*original = output;
}
