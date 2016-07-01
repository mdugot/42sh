/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 17:57:45 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/27 20:27:06 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				export_new(char *arg, char *tmp, t_shell *sh, int err)
{
	if (ft_strchr(arg, '=') && arg[0] != '=')
	{
		tmp = arg;
		while (*tmp != '=')
			tmp++;
		*tmp = 0;
		tmp++;
		if (is_correct_varname(arg, err, "export"))
			sh->env = env_add(sh->env, arg, tmp);
		else
		{
			change_status(sh, 1);
			return (1);
		}
		return (0);
	}
	else if (is_correct_varname(arg, err, "export"))
	{
		sh->env = env_add(sh->env, arg, "");
		return (0);
	}
	change_status(sh, 1);
	return (1);
}

int				export_fail(t_shell *sh, t_cmd_param *params, int err)
{
	if (ft_strcmp(params->param, "fail") == 0)
	{
		ft_printf_fd(err, "42sh: export: %s: invalid option\n",
			params->args->param);
		ft_printf_fd(err, "export: usage: export [-p] var[=content] ...\n");
		change_status(sh, 1);
		return (1);
	}
	return (0);
}

static int		do_export_2(t_cmd_param **tmparg, t_shell *sh, int err)
{
	char		*tmp;
	int			error;

	error = 0;
	if (find_existing_param(tmparg, "other"))
	{
		(*tmparg) = (*tmparg)->args;
		while ((*tmparg))
		{
			tmp = find_env(sh->local, (*tmparg)->param);
			if (tmp)
				sh->env = env_add(sh->env, (*tmparg)->param, tmp);
			else
				error = export_new((*tmparg)->param, tmp, sh, err);
			(*tmparg) = (*tmparg)->args;
		}
	}
	return (error);
}

void			do_export(t_command *c, t_shell *sh, int out, int err)
{
	int			error;
	t_cmd_param *params;
	t_cmd_param *tmparg;

	if (c->argc <= 1)
	{
		print_env(sh->env, out);
		return ;
	}
	params = parse_arguments(c, "p", "");
	if (export_fail(sh, params, err))
		return ;
	tmparg = params;
	error = do_export_2(&tmparg, sh, err);
	if (!error && (c->argc <= 1 || find_existing_param(&params, "p")))
		print_env(sh->env, out);
	goto_begin_args(&params);
	free_options_list(&params);
}
