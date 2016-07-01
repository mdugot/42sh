/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:24:05 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 11:24:06 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "builtins.h"
#include "history.h"

static void		do_env(t_command *c, t_shell *sh)
{
	change_status(sh, 0);
	if (forge_new_env(sh, c) != 0)
	{
		change_status(sh, 1);
		quit(sh, sh->last_status);
	}
	if (c->env == NULL)
		print_env(sh->env, 1);
	else if (c->env->argc == 0)
		print_env(sh->env, 1);
	else
	{
		if (c->env->type == C_BUILTIN)
			exec_builtin(sh, c->env, 1, 2);
		else if (c->env->type == C_ERROR)
		{
			exec_error(c->env, 2);
			quit(sh, 1);
		}
		else if (c->env->type == C_BIN)
			execve(c->env->path, c->env->argv, sh->env);
	}
	quit(sh, sh->last_status);
}

static void		exit_shell(t_command *command, int fd_error)
{
	int			r;
	t_shprop	*edit;

	edit = command->shell->edit;
	r = 0;
	if (command->argc > 2)
	{
		change_status(command->shell, 1);
		return (ft_putendl_fd("exit: Expression syntax.", fd_error));
	}
	if (command->argc == 2)
	{
		if (ft_isint(command->argv[1], &r) == 0)
		{
			change_status(command->shell, 1);
			return (ft_putendl_fd("exit: Expression syntax.", fd_error));
		}
	}
	file_hist_append(edit->hist, edit->hist_fd);
	quit(command->shell, r);
}

void			exec_builtin(t_shell *sh, t_command *command,
					int fd_out, int fd_error)
{
	if (ft_strcmp(command->path, "exit") == 0)
		exit_shell(command, fd_error);
	if (ft_strcmp(command->path, "cd") == 0)
		change_directory(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "echo") == 0)
		do_echo(command, fd_out, fd_error);
	if (ft_strcmp(command->path, "set") == 0)
		set_local(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "unset") == 0)
		unset_local(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "setenv") == 0)
		set_env(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "unsetenv") == 0)
		unset_env(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "env") == 0)
		do_env(command, sh);
	if (ft_strcmp(command->path, "history") == 0)
		history(sh, command, fd_out, fd_error);
	if (ft_strcmp(command->path, "read") == 0)
		do_read(command, sh, fd_out, fd_error);
	if (ft_strcmp(command->path, "export") == 0)
		do_export(command, sh, fd_out, fd_error);
}
