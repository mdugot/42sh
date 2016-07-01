/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_useless_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:35:36 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:35:37 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*delete_useless_exp(char *path)
{
	char	*tmp;
	size_t	path_len;

	tmp = NULL;
	while (ft_strstr(path, "//"))
		path = ft_replace(path, "//", "/");
	while (ft_strstr(path, "/./"))
		path = ft_replace(path, "/./", "/");
	while (ft_strnstr(path, "./", 2))
	{
		tmp = ft_strsub(path, 2, ft_strlen(path) - 2);
		ft_str_renew(&path, tmp);
	}
	path_len = ft_strlen(path);
	if (path_len > 2)
	{
		if (ft_strcmp(&path[path_len - 2], "/.") == 0)
			path[path_len - 2] = 0;
	}
	else if (ft_strncmp(path, "/.", 2) == 0)
		path = ft_str_renew(&path, ft_strsub(path, 0, ft_strlen(path) - 1));
	if (ft_strcmp(path, ".") == 0)
		ft_str_renew(&path, ft_strdup(""));
	return (path);
}
