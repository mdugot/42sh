/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:14:16 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/21 16:17:10 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		check_fermeture(char *str, char c, char cr)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		else if (*str == cr)
			count--;
		else if (count > 0 && c == '[' &&
				(*str == '?' || *str == '*'))
			return (1);
		str++;
	}
	if (count == 0)
		return (1);
	return (0);
}

static int		check_enchevetrement(char *str)
{
	while (*str)
	{
		if (*str == '[')
		{
			while (*str && *str != ']' && *str != '}')
				str++;
			if (*str == '}')
				return (0);
			if (*str)
				str++;
			else
				return (0);
		}
		str++;
	}
	return (1);
}

int				check_error(char *str)
{
	if (check_fermeture(str, '[', ']') && check_fermeture(str, '{', '}')
		&& check_enchevetrement(str))
		return (1);
	return (0);
}
