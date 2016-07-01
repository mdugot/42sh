/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:00:35 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 20:57:23 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				syntax_error(char *line)
{
	int r;

	if (!is_closed(line, "\"'`({["))
	{
		ft_putendl_fd("42sh: parse error", 2);
		return (-1);
	}
	while ((r = go_next_syntax(&line, 0)) == 1)
		;
	if (r == -1)
		ft_putendl_fd("42sh: parse error", 2);
	return (r);
}

static int		get_char_error(char **str, int *r, int c_open, int c_close)
{
	int		result;

	result = 0;
	if ((*str)[0] == c_open)
	{
		*r = 1;
		*str += 1;
		result = 1;
		while ((result = go_next_syntax(str, c_close)) == 1)
			;
		if (*str[0] == c_close)
			*str += 1;
		else
		{
			return (1);
		}
	}
	return (result);
}

int				parenthesis_error(char **str, int *r)
{
	int	result;

	if ((*str)[0] == 0)
		return (0);
	if (((*str)[0] == '(' && *r != -1)
			|| (*str)[0] == ')')
		return (1);
	result = get_char_error(str, r, '(', ')');
	return (result);
}

int				empty_backquote(char *str)
{
	int n;

	if (*str != '`')
		return (0);
	if (*str == '`' && str[1] == '`')
		return (2);
	n = 1;
	while (ft_strchr("\t \n", str[n]))
	{
		n++;
		if (str[n] == '`')
			return (n + 1);
	}
	return (0);
}

int				backquote_error(char **str, int *r)
{
	int	result;
	int n;

	if ((*str)[0] == 0)
		return (0);
	if ((n = empty_backquote(*str)))
	{
		*r = 1;
		*str += n;
		return (0);
	}
	result = get_char_error(str, r, '`', '`');
	return (result);
}
