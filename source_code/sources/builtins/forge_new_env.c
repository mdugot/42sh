/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_new_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:08:56 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 11:08:57 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int			env_errors(int err_code, char *err_str)
{
	if (err_code == 1)
	{
		ft_printf_fd(2, "env: illegal option -- %c\n", err_str[1]);
		ft_printf_fd(2, "Usage: env [-i] [-u name]\n");
	}
	if (err_code == 2)
	{
		ft_printf_fd(2, "env: option requires an argument -- %c\n", err_str[0]);
		ft_printf_fd(2, "Usage: env [-i] [-u name]\n");
	}
	return (err_code);
}

static void			params_other(t_cmd_param *params, t_shell *shell)
{
	t_cmd_param *index;

	if (find_existing_param(&params, "other"))
	{
		index = params->args;
		while (index)
		{
			shell->env = env_arg(index->param, shell->env);
			index = index->args;
		}
	}
}

static void			env_opt_u(t_cmd_param *params, t_shell *shell)
{
	t_cmd_param		*index;

	index = params;
	while (index->args)
	{
		index = index->args;
		if (index->param)
			shell->env = env_delete(shell->env, index->param);
	}
}

int					forge_new_env(t_shell *shell, t_command *cmd)
{
	t_cmd_param	*params;
	int			ret;

	ret = 0;
	params = parse_arguments(cmd, "i", "u");
	if (!params)
		return (0);
	else if (find_existing_param(&params, "fail"))
		ret = env_errors(1, params->args->param);
	else if (find_existing_param(&params, "i"))
	{
		ft_freetab(shell->env);
		shell->env = (char **)ft_memalloc(sizeof(char *));
	}
	else if (find_existing_param(&params, "u"))
	{
		if (!params->args)
			ret = env_errors(2, params->param);
		env_opt_u(params, shell);
	}
	params_other(params, shell);
	goto_begin_args(&params);
	free_options_list(&params);
	return (ret);
}
