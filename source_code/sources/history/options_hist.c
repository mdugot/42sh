/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 14:47:31 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/28 09:58:42 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include "history.h"

int		option_w(t_hist *hist, char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd)
	{
		goto_begin_hist(&hist);
		while (hist && hist->prev)
		{
			store_hist_line(hist->line, fd);
			hist = hist->prev;
		}
		close(fd);
	}
	return (1);
}

void	option_p(t_cmd_param *params, int len_params, int out_fd)
{
	t_cmd_param *index;

	if (find_existing_param(&params, "other"))
	{
		index = params->args;
		if (len_params > 0)
			while (index)
			{
				ft_putendl_fd(index->param, out_fd);
				index = index->args;
			}
	}
}

void	option_s(t_cmd_param *params, t_hist *hist, int len_params)
{
	t_cmd_param *index;
	char		*buf;

	if (find_existing_param(&params, "other"))
	{
		buf = ft_strnew(len_params + 1);
		index = params->args;
		while (index)
		{
			ft_strcat(buf, index->param);
			if (index->args)
				ft_strcat(buf, " ");
			index = index->args;
		}
		hist->line = buf;
		t_hist_push(&hist, t_hist_new(NULL, 0));
	}
}

void	option_c(t_shprop *shell)
{
	int fd;

	fd = 0;
	if (shell->hist_fd != -1)
	{
		fd = open(shell->hist_dir, O_CREAT | O_RDWR | O_TRUNC, 0755);
		if (fd)
		{
			close(shell->hist_fd);
			shell->hist_fd = fd;
		}
		shell->hist_trunc = 1;
		clear_history(&(shell)->hist);
	}
}
