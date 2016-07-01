/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:05:18 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:05:19 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*cd_too_many_args(t_cmd_param *params, int *fds)
{
	char	*path;

	if (count_params(params) > 1)
	{
		ft_putendl_fd("cd: too many arguments.", fds[1]);
		return (NULL);
	}
	path = ft_strdup(params->args->param);
	return (path);
}

static char		*cd_go_prev_dir(t_cmd_param *params, int **fds,
					t_shell *shell, int out_bak)
{
	char	*path;

	path = ft_strdup(params->args->param);
	if (ft_strcmp(path, "-") == 0)
	{
		(*fds)[0] = out_bak;
		ft_strdel(&path);
		path = get_oldpwd_var(shell->env, (*fds)[1]);
	}
	else
	{
		ft_printf_fd((*fds)[1], "42sh: cd: %s: invalid option\n", path);
		ft_printf_fd((*fds)[1], "cd: usage: cd [LP] [dir]\n");
		ft_strdel(&path);
		return (NULL);
	}
	return (path);
}

int				check_params(t_cmd_param *params, t_shell *shell, int *fds,
					char **path)
{
	int out_bak;

	out_bak = fds[0];
	fds[0] = -1;
	if (!params)
		*path = get_home_var(shell->env, fds[1]);
	else if (find_existing_param(&params, "other"))
		*path = cd_too_many_args(params, fds);
	else if (ft_strcmp(params->param, "fail") == 0)
		*path = cd_go_prev_dir(params, &fds, shell, out_bak);
	else
		*path = get_home_var(shell->env, fds[1]);
	if (*path == NULL)
		return (0);
	return (1);
}
