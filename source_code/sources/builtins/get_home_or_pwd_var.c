/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home_or_pwd_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:20:35 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:20:37 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*get_home_var(char **env, int err)
{
	char	*path;

	path = find_env(env, "HOME");
	if (path == NULL)
	{
		ft_putendl_fd("cd: No home directory.", err);
		return (NULL);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putendl_fd("cd: Can't change to home directory.", err);
		return (NULL);
	}
	return (ft_strdup(path));
}

char		*get_oldpwd_var(char **env, int err)
{
	char	*path;

	path = find_env(env, "OLDPWD");
	if (path == NULL)
	{
		ft_putendl_fd("cd: OLDPWD not set.", err);
		return (NULL);
	}
	if (access(path, F_OK) == -1)
	{
		cd_error(err, path);
		return (NULL);
	}
	return (ft_strdup(path));
}
