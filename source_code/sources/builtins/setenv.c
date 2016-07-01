/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:29:04 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/25 17:14:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh42.h"

void	set_env(t_command *c, t_shell *sh, int out, int err)
{
	change_status(sh, 1);
	if (c->argc <= 1)
	{
		change_status(sh, 0);
		return (print_env(sh->env, out));
	}
	else if (c->argc > 3)
		return (ft_putendl_fd("setenv: Too many arguments.", err));
	if (!is_correct_varname(c->argv[1], err, "setenv"))
		return ;
	change_status(sh, 0);
	sh->env = env_add(sh->env, c->argv[1], c->argv[2]);
}
