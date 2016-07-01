/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:13:43 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 16:18:46 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		verify_fd_out(t_list *list, int id)
{
	t_out *out;

	if (id == 1 || id == 2 || id == CLOSED)
		return (0);
	if (list == NULL)
		return (-1);
	out = (t_out*)list->content;
	if (out->id == id)
		return (0);
	return (verify_fd_out(list->next, id));
}

int		verify_fd_in(t_list *list, int id)
{
	t_in *in;

	if (id == 0 || id == CLOSED)
		return (0);
	if (list == NULL)
		return (-1);
	in = (t_in*)list->content;
	if (in->id == id)
		return (0);
	return (verify_fd_in(list->next, id));
}

void	add_agg_to(int *fd, int n)
{
	fd[n] = 1;
	if (n != CLOSED)
		fd[CLOSED] = 0;
}

int		convert_in_redirection(t_command *c, t_dir_type type, char *fd)
{
	if (type == DT_IN)
		return (add_redirection_in(c, 0, fd, 0));
	else if (type == DT_OUT)
		return (add_redirection_out(c, 1, fd, 0));
	else
		return (add_redirection_out(c, 2, fd, 0));
}

int		add_aggregation(t_command *c, t_dir_type type, char *fd)
{
	int		n;

	if (type == DT_NULL)
		return (command_error(c, "Bad file descriptor", NULL));
	if (fd == NULL || *fd == 0)
		return (command_error(c, "Missing name for redirect", NULL));
	if (ft_strcmp("-", fd) && !is_positive_number(fd))
		return (convert_in_redirection(c, type, fd));
	if (*fd == '-')
		n = CLOSED;
	else
		n = read_positive_number(&fd, 256);
	if (type == DT_IN)
		add_agg_to(c->fd_in, n);
	else if (type == DT_OUT)
		add_agg_to(c->fd_out, n);
	else
		add_agg_to(c->fd_error, n);
	return (0);
}
