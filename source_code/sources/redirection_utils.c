/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:21:22 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 21:29:26 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

int		is_default_in(int *fd, t_list *list, t_command *c)
{
	t_in	*in;

	if (c->pipe_previous != NULL)
		return (0);
	if (list == NULL)
		return (1);
	in = (t_in*)list->content;
	if (fd[in->id] != 0)
		return (0);
	return (is_default_in(fd, list->next, c));
}

int		is_default_out(int *fd, t_list *list, t_command *c)
{
	t_out	*out;

	if (c->pipe != NULL)
		return (0);
	if (fd[CLOSED])
		return (0);
	if (list == NULL)
		return (1);
	out = (t_out*)list->content;
	if (fd[out->id] != 0)
		return (0);
	return (is_default_out(fd, list->next, c));
}

int		add_redirection_out(t_command *c, int id, char *file, int append)
{
	t_out out;

	if (file == NULL || *file == 0)
		return (command_error(c, "Missing name for redirect", NULL));
	out.append = append;
	out.id = id;
	out.file_to_close = 1;
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (command_error(c, "Permission denied", file));
	if (is_directory(file))
		return (command_error(c, "Is a directory", file));
	if (append <= -1)
		out.fd = open(file, O_WRONLY | O_CREAT, 0666);
	else if (append)
		out.fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		out.fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out.fd <= -1)
		return (command_error(c, "No such file or directory", file));
	ft_lstadd_end(&(c->list_out), ft_lstnew(&out, sizeof(t_out)));
	return (0);
}

int		add_redirection_in(t_command *c, int id, char *arg, int eof)
{
	t_in in;

	if (arg == NULL || *arg == 0)
		return (command_error(c, "Missing name for redirect", NULL));
	in.eof = NULL;
	in.buff = NULL;
	in.fd = -1;
	in.id = id;
	if (eof)
		pipe_error_eof(&in, arg, c);
	else
		pipe_error_file(&in, arg, c);
	ft_lstadd_end(&(c->list_in), ft_lstnew(&in, sizeof(t_in)));
	ft_strdel(&in.eof);
	return (0);
}
