/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 14:49:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/27 18:48:25 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int			goto_begin_hist(t_hist **hist)
{
	int		i;

	i = 0;
	while (*hist && (*hist)->next)
	{
		*hist = (*hist)->next;
		i++;
	}
	return (i);
}

int			goto_end_hist(t_hist **hist)
{
	int		i;

	i = 0;
	while (*hist && (*hist)->prev)
	{
		*hist = (*hist)->prev;
		i++;
	}
	return (i);
}

int			clear_history(t_hist **hist)
{
	goto_begin_hist(hist);
	while ((*hist)->prev)
	{
		*hist = (*hist)->prev;
		free((*hist)->next->line);
		free((*hist)->next);
		(*hist)->next = NULL;
	}
	return (1);
}

static void	padding_int(int padding, int to_print, int out_fd)
{
	int	size_to_print;
	int	tmp;

	tmp = to_print;
	size_to_print = 0;
	while (tmp)
	{
		tmp /= 10;
		size_to_print += 1;
	}
	while (size_to_print < padding)
	{
		ft_putstr_fd(" ", out_fd);
		size_to_print++;
	}
	ft_putnbr_fd(to_print, out_fd);
}

void		print_history_line(t_hist *hist, int i, int padding, int out_fd)
{
	padding_int(padding, i, out_fd);
	ft_putstr_fd(" ", out_fd);
	if (hist && hist->line)
		ft_putendl_fd(hist->line, out_fd);
}
