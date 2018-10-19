/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp_void.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 13:17:11 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/27 10:51:17 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_strcmp_void(void *p1, void *p2)
{
	char	*s1;
	char	*s2;
	int		i;

	if (!p1 || !p2)
		return (0);
	s1 = (char *)p1;
	s2 = (char *)p2;
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
