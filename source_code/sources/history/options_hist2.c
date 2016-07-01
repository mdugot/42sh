/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_hist2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:58:49 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 09:59:00 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include "history.h"

int		option_r(t_command *cmd, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd)
	{
		hist_update(cmd->shell->edit, fd);
		close(fd);
	}
	return (1);
}

int		option_a(t_hist *hist, char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0755);
	if (fd)
	{
		file_hist_append(hist, fd);
		close(fd);
	}
	return (1);
}

void	option_n(t_command *cmd, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd)
		get_history(cmd->shell->edit, fd);
}
