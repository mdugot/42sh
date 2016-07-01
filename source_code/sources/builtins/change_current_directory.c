/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_logic_wd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:38:09 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:38:10 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*get_logic_wd(t_shell *shell, t_cmd_param *params,
					char *path, int i)
{
	char	*logic_cwd;

	logic_cwd = NULL;
	if (find_existing_param(&params, "P"))
	{
		ft_strdel(&(shell)->cwd);
		ft_strdel(&path);
		return (getcwd(shell->cwd, 0));
	}
	else
	{
		path = delete_useless_exp(path);
		i = ft_strlen(path) - 1;
		if (path[i] == '/' && i != 0)
			path[i] = 0;
		if (path[0] != '/')
			logic_cwd = join_paths(shell->cwd, path);
		else
			logic_cwd = ft_strdup(path);
		logic_cwd = reduce_path(logic_cwd);
		if (ft_strlen(logic_cwd) == 0)
			ft_str_renew(&logic_cwd, ft_strdup("/"));
	}
	ft_strdel(&path);
	return (logic_cwd);
}

static char		*get_tmp_cwd(t_cmd_param *params, t_shell *shell, char *path)
{
	char		*tmp;

	tmp = get_logic_wd(shell, params, ft_strdup(path), 0);
	if (chdir(tmp) == -1)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	shell->env = env_add(shell->env, "OLDPWD", shell->cwd);
	return (tmp);
}

int				change_current_directory(t_shell *shell, t_cmd_param *params,
					char *path, int *fds)
{
	char	*tmp;

	tmp = NULL;
	if (find_existing_param(&params, "P"))
	{
		if (chdir(path) == -1)
			return (cd_error(fds[1], path));
		shell->env = env_add(shell->env, "OLDPWD", shell->cwd);
		shell->cwd = get_logic_wd(shell, params, ft_strdup(path), 0);
	}
	else
	{
		tmp = get_tmp_cwd(params, shell, path);
		if (tmp == NULL)
			return (cd_error(fds[1], path));
		ft_strdel(&shell->cwd);
		shell->cwd = tmp;
	}
	change_status(shell, 0);
	shell->env = env_add(shell->env, "PWD", shell->cwd);
	if (fds[0] > -1)
		ft_putendl_fd(shell->cwd, fds[0]);
	return (1);
}
