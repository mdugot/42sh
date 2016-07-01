/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:00:09 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:00:10 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				cd_error(int err, char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_printf_fd(err, "cd: No such file or directory: %s\n", path);
		return (-1);
	}
	else if (is_directory(path) == 0)
	{
		ft_printf_fd(err, "cd: Is not a directory: %s\n", path);
		return (-1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_printf_fd(err, "cd: Permission denied: %s\n", path);
		return (-1);
	}
	return (0);
}
