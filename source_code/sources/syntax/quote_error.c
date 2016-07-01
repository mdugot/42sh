/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:12:15 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 20:57:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		get_start_inside(char *begin, char **str, int *i, int *r)
{
	int		inside;

	inside = update_inside(begin, *str, i, "{['\"");
	if (inside)
	{
		*r = 1;
		*i += 1;
	}
	return (inside);
}

static int		move_inside(char **str, int *r)
{
	int			i;
	int			inside;
	char		begin;

	i = 0;
	begin = 0;
	inside = get_start_inside(&begin, str, &i, r);
	while (inside)
	{
		if ((*str)[i] == '\0')
			return (-1);
		inside += update_inside(&begin, *str, &i, "{['\"");
		i++;
	}
	return (i);
}

static int		get_quote_error(char **str, int *r, int end)
{
	int		i;

	i = move_inside(str, r);
	if (i == -1)
		return (-1);
	*str += i;
	if (ft_strchr("\\{[(\"'", *str[0]))
		return (quote_error(str, r, end));
	return (0);
}

int				quote_error(char **str, int *r, int end)
{
	pass_backquote(str, r);
	if (*str[0] == '\0' || *str[0] == end)
		return (0);
	if (parenthesis_error(str, r)
			|| backquote_error(str, r))
		return (-1);
	if (*str[0] == '\0' || *str[0] == end)
		return (0);
	if (ft_strchr("}])", *str[0]))
		return (-1);
	return (get_quote_error(str, r, end));
}
