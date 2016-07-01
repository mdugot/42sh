/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 16:50:08 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 15:27:32 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	free_in(void *ad, size_t s)
{
	t_in *in;

	(void)s;
	if (ad == NULL)
		return ;
	in = (t_in*)ad;
	if (in->eof == NULL && in->fd > 2)
		close(in->fd);
	if (in->buff)
		ft_strdel(&in->buff);
	ft_memdel((void**)&in);
}

void	free_out(void *ad, size_t s)
{
	t_out *out;

	(void)s;
	if (ad == NULL)
		return ;
	out = (t_out*)ad;
	if (out->file_to_close && out->fd > 2)
		close(out->fd);
	ft_memdel((void**)&out);
}

void	free_command(t_command *c)
{
	int i;

	if (c == NULL)
		return ;
	free_command(c->env);
	free_command(c->next);
	free_command(c->pipe);
	ft_strdel(&c->line);
	ft_strdel(&c->path);
	ft_strdel(&c->error_message);
	ft_strdel(&c->error_name);
	i = 0;
	while (c->argv && c->argv[i])
	{
		ft_strdel(&c->argv[i]);
		i++;
	}
	ft_memdel((void**)&c->argv);
	ft_lstdel(&c->list_out, free_out);
	ft_lstdel(&c->list_in, free_in);
	ft_memdel((void**)&c);
}

void	free_shell(t_shell *sh)
{
	int i;

	ft_strdel(&sh->cwd);
	i = 0;
	while (sh->env != NULL && sh->env[i])
	{
		ft_strdel(&sh->env[i]);
		i++;
	}
	i = 0;
	while (sh->local != NULL && sh->local[i])
	{
		ft_strdel(&sh->local[i]);
		i++;
	}
	free_shprop(&(sh)->edit);
	ft_memdel((void**)&sh->env);
	ft_memdel((void**)&sh->local);
	ft_memdel((void**)&sh);
}
