/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_outils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:30:48 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 17:20:50 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>
#include <stdlib.h>

int				is_extern_builtin(t_command *c)
{
	if (c->type != C_BUILTIN)
		return (0);
	if (ft_strcmp("env", c->path) == 0)
		return (1);
	if (c->pipe)
		return (1);
	if (c->pipe_previous)
		return (1);
	return (0);
}

static void		execute_shell(t_shell *sh, CMD *c, int fd_out, int fd_error)
{
	sh->inside_status = 1;
	if (c->type == C_ERROR)
	{
		exec_error(c, fd_error);
		change_status(sh, 1);
	}
	else if (c->type == C_BUILTIN && !is_extern_builtin(c))
		exec_builtin(sh, c, fd_out, fd_error);
	else
		sh->inside_status = 0;
}

int				execute_all(t_shell *sh, CMD *c, int pip_sh[2][2],
					int pip[2][2])
{
	int	status;

	if (!is_default_out(c->fd_out, c->list_out, c))
		dup2(pip[0][1], 1);
	if (!is_default_out(c->fd_error, c->list_out, c))
		dup2(pip[1][1], 2);
	close(pip[0][0]);
	close(pip[1][0]);
	close(pip_sh[0][1]);
	close(pip_sh[1][1]);
	status = execute_extern(sh, c, pip_sh[0][0], pip_sh[1][0]);
	close(pip_sh[0][0]);
	close(pip_sh[1][0]);
	close(pip[0][1]);
	close(pip[1][1]);
	return (status);
}

void			exe_prepa(t_shell *sh, CMD *c, int pip_out[2], int pip_error[2])
{
	close(pip_out[0]);
	close(pip_error[0]);
	execute_shell(sh, c, pip_out[1], pip_error[1]);
	close(pip_out[1]);
	close(pip_error[1]);
}
