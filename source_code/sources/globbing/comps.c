/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 16:52:57 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/21 14:35:38 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	init_strncmp(size_t *i, size_t *y, char *s1, char *s2)
{
	*i = 0;
	*y = 0;
	if (ft_glob_strlen(s2) > ft_glob_strlen(s1))
	{
		return (0);
	}
	return (-1);
}

static void	incrementation(size_t *i, size_t *y)
{
	(*i)++;
	(*y)++;
}

static int	free_bracket(char *bracket)
{
	free(bracket);
	return (1);
}

int			glob_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	y;
	char	*bracket;

	if (n == 0 || init_strncmp(&i, &y, s1, s2) != -1)
		return (n);
	while (s1[i] != '\0' && i < n)
	{
		if (s2[y] == '[')
		{
			y++;
			bracket = make_bracket(s2, y);
			if (bracket == NULL)
				return (1);
			if ((ft_strchr(bracket, s1[i])) == NULL)
				return (free_bracket(bracket));
			free(bracket);
			while (s2[y] != ']')
				y++;
		}
		else if (s1[i] != s2[y] && s2[y] != '?')
			return ((unsigned char)s1[i] - (unsigned char)s2[y]);
		incrementation(&i, &y);
	}
	return (0);
}

char		*glob_strstr(char *s1, char *s2)
{
	int i;

	if (*s2 == '\0')
		return ((char*)s1);
	i = 0;
	while (s1[i] != '\0')
	{
		if (glob_strncmp(s1 + i, s2, ft_glob_strlen(s2)) == 0)
			return (&(s1[i]));
		i++;
	}
	return (NULL);
}
