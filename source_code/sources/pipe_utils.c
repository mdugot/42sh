/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:42:32 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/27 18:10:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	write_in(t_in *in, int destination)
{
	if (in->eof)
	{
		if (in->buff)
			ft_putstr_fd(in->buff, destination);
	}
	else if (in->fd > -1)
		pipe_from_file(destination, in->fd);
}

int		write_out(char *buff, t_list *list, t_command *command)
{
	t_out	*out;
	int		done;
	int		next_done;

	if (list == NULL)
		return (0);
	done = 0;
	out = (t_out*)list->content;
	if (command->fd_out[out->id])
	{
		write(out->fd, buff, ft_strlen(buff));
		done = 1;
	}
	next_done = write_out(buff, list->next, command);
	if (done || next_done)
		return (1);
	else
		return (0);
}

int		write_error(char *buff, t_list *list, t_command *command)
{
	t_out	*err;
	int		done;
	int		next_done;

	if (list == NULL)
		return (0);
	done = 0;
	err = (t_out*)list->content;
	if (command->fd_error[err->id])
	{
		write(err->fd, buff, ft_strlen(buff));
		done = 1;
	}
	next_done = write_error(buff, list->next, command);
	if (done || next_done)
		return (1);
	else
		return (0);
}

void	drain_pipe(int fd)
{
	char	buff[BUFF_SIZE + 1];
	int		r;

	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
		;
	if (r == -1)
		exit_error("Read has encountered a problem.");
}
