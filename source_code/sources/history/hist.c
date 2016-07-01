/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 13:09:24 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/27 19:34:16 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh21.h"
#include "stdio.h"
#include <fcntl.h>
#include "history.h"

t_hist	*t_hist_new(char *line, int stored)
{
	t_hist *new;

	new = (t_hist *)malloc(sizeof(t_hist));
	if (new)
	{
		if (line)
			new->line = ft_strdup(line);
		else
			new->line = NULL;
		new->stored = stored;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void	t_hist_push(t_hist **first, t_hist *new)
{
	if (*first)
	{
		(*first)->prev = new;
		new->next = *first;
		*first = new;
	}
	else
		*first = new;
}

void	store_hist_line(char *line, int fd)
{
	if (fd > 0)
		ft_putendl_fd(line, fd);
}

void	file_hist_append(t_hist *hist, int fd)
{
	goto_end_hist(&hist);
	while (hist && hist->next && hist->stored == 0)
		hist = hist->next;
	while (hist && hist->line)
	{
		store_hist_line(hist->line, fd);
		hist->stored = 1;
		hist = hist->prev;
	}
}
