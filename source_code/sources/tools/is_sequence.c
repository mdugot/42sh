/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sequence.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:50:05 by mressier          #+#    #+#             */
/*   Updated: 2016/06/30 13:48:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_escaped(const char *str, char *c)
{
	int n;

	n = 0;
	c--;
	while (c >= str && *c == '\\')
	{
		n++;
		c--;
	}
	return (n % 2);
}

int			is_in(char *str, char *c, char *syntax)
{
	int		i;
	int		inside;
	char	begin;
	int		r;

	i = 0;
	inside = 0;
	begin = 0;
	while (str[i])
	{
		r = update_inside(&begin, str, &i, syntax);
		if (r)
			inside += r;
		else if (inside && ft_strchr(c, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int			is_closed(char *str, char *syntax)
{
	int		i;
	int		inside;
	char	begin;

	inside = 0;
	begin = 0;
	i = 0;
	if (str == NULL)
		return (1);
	while (str[i])
	{
		inside += update_inside(&begin, str, &i, syntax);
		i += 1;
	}
	if (i > 0 && str[i - 1] == '\\' && !is_escaped(str, &str[i - 1]))
	{
		str[i - 1] = 0;
		return (0);
	}
	return (inside ? 0 : 1);
}
