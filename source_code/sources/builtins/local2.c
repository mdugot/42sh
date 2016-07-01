/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:41:39 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/29 10:41:57 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		set_local(t_command *c, t_shell *sh, int out, int err)
{
	change_status(sh, 1);
	if (c->argc <= 1)
	{
		change_status(sh, 0);
		return (print_env(sh->local, out));
	}
	else if (c->argc > 3)
		return (ft_putendl_fd("set: Too many arguments.", err));
	if (!is_correct_varname(c->argv[1], err, "set"))
		return ;
	change_status(sh, 0);
	sh->local = env_add(sh->local, c->argv[1], c->argv[2]);
}

void		unset_local(t_command *c, t_shell *sh, int out, int err)
{
	int i;

	(void)out;
	if (c->argc <= 1)
	{
		change_status(sh, 1);
		return (ft_putendl_fd("unset: Too few arguments.", err));
	}
	i = 1;
	while (c->argv[i])
	{
		if (find_env(sh->local, c->argv[i]) == NULL)
			ft_printf_fd(err,
					"unset: Variable not found: %s.\n", c->argv[i]);
		else
			sh->local = env_delete(sh->local, c->argv[i]);
		i++;
	}
}
