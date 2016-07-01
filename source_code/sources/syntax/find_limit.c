/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_limit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:53:46 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 14:53:49 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_opposite_syntax(int c)
{
	if (c == '(')
		return (')');
	else if (c == '{')
		return ('}');
	else if (c == '[')
		return (']');
	else
		return (c);
}

void		find_limit(char c, char *begin, char *end)
{
	if (ft_strchr("\"'`([{", c) == NULL)
	{
		*begin = 0;
		*end = 0;
	}
	else
	{
		*begin = c;
		*end = get_opposite_syntax(c);
	}
}
