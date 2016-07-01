/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:02:15 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 17:19:16 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>

void		do_subshell(t_shell *shell, char *str, int b_exit)
{
	t_command	*command;

	shell->env = update_shlvl(shell->env);
	command = cut_semicolon(shell, str);
	execute(shell, command, NEXT_DEFAULT);
	free_command(command);
	if (b_exit)
		exit(shell->last_status);
}

void		subshell(t_shell *shell, t_command *cmd)
{
	if (cmd->argc > 1)
	{
		ft_printf("42sh : parse error after %s\n", cmd->path);
		exit(1);
	}
	do_subshell(shell, chop_limit(cmd->path), 1);
}
