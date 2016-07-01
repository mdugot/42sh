/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:13:41 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/30 13:38:47 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>

int		get_eof_input(t_shprop *shell, char **line)
{
	int		ret;

	ft_strdel(&(shell)->input);
	ft_strdel(&(shell)->prompt);
	shell->prompt = ft_strdup("");
	ft_putstr_fd(shell->prompt, shell->term->fd);
	shell->prompt_len = 0;
	shell->curs_pos = 0;
	ret = get_input(shell, &handle_edit_keys);
	if (shell->input)
		*line = ft_strdup(shell->input);
	else if (interrupt(-1) == 0)
		*line = ft_strdup("");
	return (ret);
}

void	charge_eof(t_in *in, t_shell *sh)
{
	int		r;
	char	*line;
	char	*tmp;

	line = NULL;
	in->buff = NULL;
	while ((r = get_eof_input(sh->edit, &line)) > 0)
	{
		if (ft_strcmp(line, in->eof) == 0)
		{
			ft_strdel(&line);
			return ;
		}
		tmp = in->buff;
		if (tmp)
		{
			in->buff = ft_strf("%s%s\n", tmp, line);
			ft_strdel(&tmp);
		}
		else
			in->buff = ft_strf("%s\n", line);
		ft_strdel(&line);
	}
	if (r == -1)
		exit_error("Get_next_line has encountered an error.");
}

int		pipe_error_eof(t_in *in, char *eof, t_command *c)
{
	if (eof == NULL || *eof == 0)
		return (command_error(c, "Parse error", NULL));
	in->eof = ft_strdup(eof);
	charge_eof(in, c->shell);
	return (0);
}

void	pipe_from_file(int fd, int file)
{
	char	buff[BUFF_SIZE + 1];
	int		r;

	while ((r = read(file, buff, BUFF_SIZE)) > 0)
	{
		if (interrupt(-1) == 1)
			return ;
		buff[r] = '\0';
		write(fd, buff, r);
	}
	if (r == -1)
		exit_error("Read has encountered a problem.");
}

int		pipe_error_file(t_in *in, char *name, t_command *c)
{
	if (name == NULL || *name == 0)
		return (command_error(c, "Missing name for redirect", NULL));
	if (access(name, F_OK) == -1)
		return (command_error(c, "No such file or directory", name));
	if (access(name, R_OK) == -1)
		return (command_error(c, "Permission denied", name));
	if (is_directory(name))
		return (command_error(c, "Is a directory", name));
	in->fd = open(name, O_RDONLY);
	if (in->fd <= -1)
		return (command_error(c, "Can not open file", name));
	return (0);
}
