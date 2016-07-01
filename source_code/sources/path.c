/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:09:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/05/07 17:15:57 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>

char	**env_paths(char **env)
{
	char *paths;

	paths = find_env(env, "PATH");
	if (paths == NULL)
		return (NULL);
	return (ft_strsplit(paths, ':'));
}

int		bin_in_dir(char *dir, char *bin, int *pd)
{
	char	*tmp;
	int		r;

	if (dir == NULL || bin == NULL)
		return (0);
	tmp = ft_strnew(ft_strlen(dir) + ft_strlen(bin) + 2);
	ft_strcat(tmp, dir);
	if (dir[ft_strlen(dir) - 1] != '/' && *bin != '/')
		ft_strcat(tmp, "/");
	ft_strcat(tmp, bin);
	r = 0;
	if (access(tmp, F_OK) == 0)
	{
		if (access(tmp, X_OK) == -1)
			*pd = 1;
		else
			r = 1;
	}
	ft_strdel(&tmp);
	return (r);
}

char	*bin_absolute_path(char *bin, int *pd)
{
	if (bin_in_dir("", bin, pd))
		return (ft_strdup(""));
	else
		return (NULL);
}

char	*bin_path(t_shell *shell, char **env, char *bin, int *pd)
{
	char	**paths;
	char	*result;
	int		i;

	if (*bin == '/')
		return (bin_absolute_path(bin, pd));
	if (bin_in_dir(shell->cwd, bin, pd) && ft_strchr(bin, '/'))
		return (ft_strdup(shell->cwd));
	i = 0;
	paths = env_paths(env);
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		if (bin_in_dir(paths[i], bin, pd))
		{
			result = ft_strdup(paths[i]);
			ft_deltab((void*)paths, ft_strsplit_size(paths));
			return (result);
		}
		i++;
	}
	ft_deltab((void*)paths, ft_strsplit_size(paths));
	return (NULL);
}
