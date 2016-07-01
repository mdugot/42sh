/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:46:05 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 09:46:22 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh21.h"
#include "stdio.h"
#include <fcntl.h>
#include "history.h"

int		get_history(t_shprop *shell, int fd)
{
	int		ret;
	char	*line;
	t_hist	*hist;

	hist = NULL;
	line = NULL;
	ret = 1;
	if (fd == -1)
		ret = -1;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line))
		{
			line = ft_replace(line, "\033", "");
			t_hist_push(&hist, t_hist_new(line, 1));
		}
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	t_hist_push(&hist, t_hist_new(NULL, 0));
	shell->hist = hist;
	return (ret);
}

void	goto_end_list(t_shprop *shell)
{
	if (shell && shell->hist)
		while (shell->hist->prev)
			shell->hist = shell->hist->prev;
}

void	append_hist(t_shprop *shell)
{
	t_hist	*hist;

	hist = shell->hist;
	if (hist)
	{
		goto_end_list(shell);
		if (!hist->next || ft_strcmp(shell->input, hist->next->line) != 0)
		{
			ft_strdel(&(shell->hist)->line);
			shell->hist->line = ft_strdup(shell->input);
			t_hist_push(&(shell)->hist, t_hist_new(NULL, 0));
		}
		else
			ft_strdel(&(shell->hist)->line);
	}
}

int		hist_delete_current_item(t_hist **hist)
{
	t_hist *to_del;

	to_del = *hist;
	if (*hist)
	{
		if ((*hist)->next)
			to_del->next->prev = to_del->prev;
		if ((*hist)->prev)
			to_del->prev->next = to_del->next;
		while ((*hist)->prev)
			*hist = (*hist)->prev;
		free(to_del->line);
		free(to_del);
	}
	return (0);
}

int		hist_update(t_shprop *shell, int fd)
{
	char	*line;
	int		gnl_ret;

	gnl_ret = 0;
	line = NULL;
	if (fd)
	{
		goto_end_list(shell);
		if (fd == 0)
			fd = shell->hist_fd;
		while ((gnl_ret = get_next_line(fd, &line)) && gnl_ret > 0)
		{
			if (ft_strlen(line))
			{
				shell->hist->line = ft_strdup(line);
				shell->hist->stored = 1;
				t_hist_push(&(shell)->hist, t_hist_new(NULL, 0));
			}
			free(line);
		}
		free(line);
	}
	return (gnl_ret);
}
