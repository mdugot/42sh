/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_ad_send.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:40:01 by mressier          #+#    #+#             */
/*   Updated: 2016/06/30 14:22:51 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		do_receipt_and_execute(int pip[2], t_shell *sh, t_command *c)
{
	int		child2;
	int		status;

	close(pip[1]);
	child2 = receipt_and_execute(sh, c->pipe, pip[0]);
	waitpid(child2, &status, 0);
	close(pip[0]);
}

pid_t			send_error(t_command *c, int error, int pip[2])
{
	pipe_error(c, error, pip[1]);
	close(pip[1]);
	exit(0);
	return (0);
}

pid_t			distrib_and_send(t_shell *sh, t_command *c, int output,
					int error)
{
	pid_t	child;
	pid_t	child2;
	int		pip[2];
	int		status;

	child = 0;
	ft_bzero(pip, sizeof(int) * 2);
	pip[1] = -1;
	if (c->pipe)
		pipe(pip);
	child = my_fork();
	if (child)
	{
		if (c->pipe)
			do_receipt_and_execute(pip, sh, c);
		return (child);
	}
	close(pip[0]);
	child2 = my_fork();
	if (!child2)
		send_error(c, error, pip);
	pipe_out(c, output, pip[1]);
	close(pip[1]);
	waitpid(child2, &status, 0);
	return (quit(sh, 0));
}
