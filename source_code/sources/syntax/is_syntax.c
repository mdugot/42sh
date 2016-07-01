/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:39:49 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 12:40:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		begin_with(char **line, const char *begin)
{
	char *str;

	str = *line;
	if (ft_strncmp(str, begin, ft_strlen(begin)) == 0)
	{
		*line += ft_strlen(begin);
		return (1);
	}
	else
		return (0);
}

static int		begin_with_number_and(char **line, const char *begin)
{
	char	*str;
	int		n;

	str = *line;
	n = len_number(*line);
	if (!n)
		return (0);
	str += n;
	if (ft_strncmp(str, begin, ft_strlen(begin)) == 0)
	{
		*line = str + ft_strlen(begin);
		return (n + ft_strlen(begin));
	}
	return (0);
}

int				is_syntax(char **str)
{
	if (begin_with(str, "&&")
			|| begin_with(str, "||")
			|| begin_with(str, ";")
			|| begin_with(str, "|"))
		return (1);
	return (0);
}

int				is_redirection(char **str)
{
	int len;

	if ((len = begin_with_number_and(str, ">&"))
			|| (len = begin_with_number_and(str, "<&"))
			|| (len = begin_with_number_and(str, "<<"))
			|| (len = begin_with_number_and(str, ">>"))
			|| (len = begin_with_number_and(str, "<>"))
			|| (len = begin_with_number_and(str, ">"))
			|| (len = begin_with_number_and(str, "<")))
		return (len);
	if (begin_with(str, ">&")
		|| begin_with(str, "<&")
		|| begin_with(str, "<<")
		|| begin_with(str, ">>"))
		return (2);
	if (begin_with(str, ">") || begin_with(str, "<"))
		return (1);
	return (0);
}
