/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:26:43 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:26:44 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*get_new_path(char *path, int start, int i)
{
	int		len;
	char	*tmp;

	len = i - start + 3;
	tmp = ft_strnew(ft_strlen(path) - len + 1);
	ft_strncat(tmp, path, start);
	ft_strcat(tmp, &path[start + len]);
	free(path);
	return (tmp);
}

char			*reduce_path(char *path)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (path[i])
	{
		if (ft_strncmp(&path[i], "/..", 3) == 0)
		{
			path = get_new_path(path, start, i);
			i = -1;
		}
		else if (path[i] == '/')
			start = i;
		i++;
	}
	return (path);
}
