/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 15:28:50 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 17:46:06 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh42.h"

void	unset_env(t_command *c, t_shell *sh, int out, int err)
{
	int i;

	(void)out;
	if (c->argc <= 1)
	{
		change_status(sh, 1);
		return (ft_putendl_fd("unsetenv: Too few arguments.", err));
	}
	i = 1;
	while (c->argv[i])
	{
		if (find_env(sh->env, c->argv[i]) == NULL)
			ft_printf_fd(err,
					"unsetenv: Variable not found: %s.\n", c->argv[i]);
		else
			sh->env = env_delete(sh->env, c->argv[i]);
		i++;
	}
}
