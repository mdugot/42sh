/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_limit_begin_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:27:40 by mressier          #+#    #+#             */
/*   Updated: 2016/06/30 13:53:37 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_limit_begin(char *str, char *c, char *begin_str)
{
	(void)str;
	if (*c == '\0')
		return (0);
	else if (ft_strchr(begin_str, *c))
		return (1);
	return (0);
}

int			is_limit_end(char *str, char *ac, char begin)
{
	char c;

	(void)str;
	c = *ac;
	if (c == '\0')
		return (0);
	if ((ft_strchr("\"`'", c) && c == begin)
			|| (begin == '(' && c == ')')
			|| (begin == '[' && c == ']')
			|| (begin == '{' && c == '}'))
		return (1);
	return (0);
}
