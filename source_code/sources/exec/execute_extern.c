/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:54:37 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:54:38 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		exec_by_type(t_command *c, t_shell *sh)
{
	if (c->type == C_BIN)
		execve(c->path, c->argv, sh->env);
	else if (c->type == C_SUBSHELL)
		subshell(sh, c);
	else if (c->type == C_BUILTIN && is_extern_builtin(c))
		exec_builtin(sh, c, 1, 2);
}

int				execute_extern(t_shell *sh, CMD *c, int fd_out, int fd_error)
{
	pid_t	child;
	int		status;

	child = my_fork();
	if (!child)
	{
		write_output_shell(fd_out, fd_error);
		exec_by_type(c, sh);
		quit(sh, 0);
		return (0);
	}
	else
	{
		(void)c;
		sh->to_kill = child;
		waitpid(child, &status, 0);
		if (!is_default_in(c->fd_in, c->list_in, c))
			drain_pipe(0);
		if (c->type == C_VOID)
			return (0);
		return (exit_status(status, sh));
	}
}
