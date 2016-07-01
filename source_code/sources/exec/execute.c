/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 15:05:44 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 17:27:25 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>
#include <stdlib.h>

void	execute(t_shell *shell, t_command *command, t_next_type next_type)
{
	int		status;
	pid_t	child;

	(void)status;
	shell->inside_status = 0;
	if ((next_type == NEXT_DEFAULT)
		|| (next_type == NEXT_AND && shell->last_status == 0)
		|| (next_type == NEXT_OR && shell->last_status != 0))
	{
		child = receipt_and_execute(shell, command, -1);
		waitpid(child, &status, 0);
	}
	if (command->next)
		execute(shell, command->next, command->next_type);
}
