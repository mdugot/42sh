/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:19:34 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/23 18:30:49 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		pipe_error2(t_command *c, char buff[BUFF_SIZE + 1], int r)
{
	if (c->fd_error[1])
		write(1, buff, r);
	else if (c->fd_error[2])
		write(2, buff, r);
}

void			pipe_error(t_command *c, int error, int send_to)
{
	char	buff[BUFF_SIZE + 1];
	int		r;
	int		piped;

	piped = 0;
	while ((r = read(error, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		if (c->fd_error[CLOSED] == 0)
		{
			if (send_to > -1 && c->fd_error[1])
			{
				piped = 1;
				write(send_to, buff, r);
			}
			if (!write_error(buff, c->list_out, c) && c->fd_error[2] && !piped)
				pipe_error2(c, buff, r);
		}
	}
	if (r == -1)
		exit_error("1 Read has encountered a problem.");
}

void			pipe_out(t_command *c, int output, int send_to)
{
	char	buff[BUFF_SIZE + 1];
	int		r;

	while ((r = read(output, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		if (c->fd_out[CLOSED] == 0)
		{
			if (send_to > -1)
				write(send_to, buff, r);
			if (!write_out(buff, c->list_out, c) && send_to == -1)
			{
				if (c->fd_out[2])
					write(2, buff, r);
				else if (c->fd_out[1])
					write(1, buff, r);
			}
		}
	}
	if (r == -1)
		exit_error("2 Read has encountered a problem.");
}

void			pipe_in(t_list *list, t_command *c, int input, int receive_from)
{
	t_in	*in;

	if (receive_from > -1)
		pipe_from_file(input, receive_from);
	if (list == NULL)
		return ;
	in = (t_in*)list->content;
	if (c->fd_in[in->id] && !c->fd_in[CLOSED])
		write_in(in, input);
	pipe_in(list->next, c, input, -1);
}
