/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receipt_and_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:47:57 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 16:07:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		do_execute_and_distrib(t_shell *sh, t_command *c, int pip[2])
{
	pid_t	child2;
	int		status;

	status = 0;
	close(pip[1]);
	child2 = execute_and_distrib(sh, c);
	close(pip[0]);
	waitpid(child2, &status, 0);
	if (sh->inside_status == 0 && c->pipe == NULL)
		change_status(sh, exit_status(status, sh));
	dup2(sh->save_in, 0);
}

pid_t			receipt_and_execute(t_shell *sh, t_command *c, int receipt_fd)
{
	pid_t	child;
	int		pip[2];

	pipe(pip);
	decompose_command(sh, c->line, c);
	child = my_fork();
	if (child)
	{
		if (!is_default_in(c->fd_in, c->list_in, c))
			dup2(pip[0], 0);
		do_execute_and_distrib(sh, c, pip);
		return (child);
	}
	else
	{
		close(pip[0]);
		if (!is_default_in(c->fd_in, c->list_in, c))
			pipe_in(c->list_in, c, pip[1], receipt_fd);
		close(pip[1]);
		return (quit(sh, 0));
	}
}
