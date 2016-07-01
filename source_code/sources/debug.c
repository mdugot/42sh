/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 14:42:29 by mdugot            #+#    #+#             */
/*   Updated: 2016/05/07 17:13:58 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_fd(t_command *c)
{
	int			i;

	i = 0;
	ft_printf("FD LIST\n");
	while (i < 10)
	{
		if (c->fd_in[i] || c->fd_out[i] || c->fd_error[i])
		{
			ft_printf("FD %d = ", i);
			if (c->fd_in[i])
				ft_printf("(in) ");
			if (c->fd_out[i])
				ft_printf("(out) ");
			if (c->fd_error[i])
				ft_printf("(error) ");
			ft_printf("\n");
		}
		i++;
	}
}

void	print_in(t_list *elem)
{
	t_in *in;

	if (elem == NULL || elem->content == NULL)
		return ;
	in = (t_in*)elem->content;
	ft_printf("------->id=%d/fd=%d/eof=%s\n", in->id, in->fd, in->eof);
	print_in(elem->next);
}

void	print_out(t_list *elem)
{
	t_out *out;

	if (elem == NULL || elem->content == NULL)
		return ;
	out = (t_out*)elem->content;
	ft_printf("------->id=%d/to close=%d/append=%d\n", \
			out->id, out->file_to_close, out->append);
	print_out(elem->next);
}

void	print_liaison(t_next_type type)
{
	if (type == NEXT_OR)
		ft_printf("\n//////////////////   OR   ////////////////\n\n");
	else if (type == NEXT_AND)
		ft_printf("\n/////////////////   AND   ////////////////\n\n");
	else
		ft_printf("\n//////////////////////////////////////////\n\n");
}

void	print_command(t_command *c)
{
	int	i;

	ft_printf("PATH = %s\nARG = %d ->", c->path, c->argc);
	i = -1;
	while (++i < c->argc)
		ft_printf("%s/", c->argv[i]);
	ft_printf("\nERROR = %s : %s\n", c->error_name, c->error_message);
	ft_printf("TYPE = %d\n", c->type);
	ft_printf("DIRECTION IN : %p\n", c->list_in);
	print_in(c->list_in);
	ft_printf("DIRECTION OUT : %p\n", c->list_out);
	print_out(c->list_out);
	print_fd(c);
	if (c->pipe)
	{
		ft_printf("\t|\n\t|\n\t|\n");
		print_command(c->pipe);
	}
	if (c->next)
	{
		print_liaison(c->next_type);
		print_command(c->next);
	}
}
