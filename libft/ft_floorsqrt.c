/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_floorsqrt.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/01 10:36:43 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 11:01:49 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_floorsqrt(int x)
{
	int start;
	int mid;
	int end;
	int res;

	if (x == 0 || x == 1)
		return (x);
	start = 0;
	end = x / 2;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == x)
			return (mid);
		if (mid * mid < x)
		{
			start = mid + 1;
			res = mid;
		}
		else
			end = mid - 1;
	}
	return (res);
}
