/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompose_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 18:18:42 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 21:21:02 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_bin(t_command *command, char *name, char *path)
{
	if (name[0] == '\0')
	{
		command_error(command, "Command not found", name);
		return ;
	}
	if (command->path)
		ft_strdel(&command->path);
	command->path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 2);
	ft_strcat(command->path, path);
	if (path[ft_strlen(path) - 1] != '/' && *name != '/')
		ft_strcat(command->path, "/");
	ft_strcat(command->path, name);
	if (is_directory(command->path))
		command_error(command, "Is a directory", name);
	else if (access(command->path, X_OK) == -1)
		command_error(command, "Permission denied", name);
	else
		command->type = C_BIN;
}

void		init_error(t_command *command, char *name, int pd)
{
	if (command->error_name)
		ft_strdel(&command->error_name);
	if (command->error_message)
		ft_strdel(&command->error_message);
	command->error_name = ft_strdup(name);
	if (pd)
		command->error_message = ft_strdup("Permission denied");
	else if (ft_strchr(name, '/'))
		command->error_message = ft_strdup("No such file or directory");
	else
		command->error_message = ft_strdup("Command not found");
	command->type = C_ERROR;
}

void		init_command(t_shell *sh, t_command *command, char *name)
{
	char	*tmp;
	int		pd;

	pd = 0;
	command->shell = sh;
	tmp = bin_path(sh, sh->env, name, &pd);
	if (is_builtin(name))
	{
		command->path = ft_strdup(name);
		command->type = C_BUILTIN;
	}
	else if (command->type == C_SUBSHELL)
	{
		command->path = ft_strdup(name);
		command->type = C_SUBSHELL;
	}
	else if (tmp)
		init_bin(command, name, tmp);
	else
		init_error(command, name, pd);
	if (tmp)
		ft_strdel(&tmp);
}

void		append_command_name(t_shell *sh, t_command *command, char *str)
{
	char	**tmp;
	int		i;

	if (command->argc == 0)
	{
		init_command(sh, command, str);
		command->fd_in[0] = 1;
		command->fd_out[1] = 1;
		command->fd_error[2] = 2;
		command->argc = 1;
		command->argv = secure_alloc(sizeof(char*) * 2);
		command->argv[0] = ft_strdup(str);
		return ;
	}
	command->argc += 1;
	tmp = secure_alloc(sizeof(char*) * (command->argc + 1));
	i = 0;
	while (i < command->argc - 1)
	{
		tmp[i] = command->argv[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	ft_memdel((void**)&(command->argv));
	command->argv = tmp;
}

void		replace_whitespace(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return ;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == '\n')
			line[i] = ' ';
		if (line[i] == '\r')
			line[i] = ' ';
		i++;
	}
}
