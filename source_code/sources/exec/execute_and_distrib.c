/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_distrib.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:28:29 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 15:32:47 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		do_pipes(int pip[2][2], int pip_sh[2][2])
{
	pipe(pip[0]);
	pipe(pip[1]);
	pipe(pip_sh[0]);
	pipe(pip_sh[1]);
}

static void		prepa_exec(t_shell *sh, t_command *c, int pip_sh[2][2],
					int pip[2][2])
{
	close(pip[0][1]);
	close(pip[1][1]);
	exe_prepa(sh, c, pip_sh[0], pip_sh[1]);
}

static void		wait_exec(int child2, int pip[2][2])
{
	int		status;

	waitpid(child2, &status, 0);
	close(pip[0][0]);
	close(pip[1][0]);
}

pid_t			execute_and_distrib(t_shell *sh, t_command *c)
{
	pid_t	child;
	pid_t	child2;
	int		pip[2][2];
	int		pip_sh[2][2];

	do_pipes(pip, pip_sh);
	child = my_fork();
	if (!child)
	{
		execute_all(sh, c, pip_sh, pip);
		handle_error_messages(sh);
		return (quit(sh, sh->last_status));
	}
	else
	{
		prepa_exec(sh, c, pip_sh, pip);
		child2 = distrib_and_send(sh, c, pip[0][0], pip[1][0]);
		wait_exec(child2, pip);
		return (child);
	}
}
