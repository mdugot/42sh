/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output_shell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:00:29 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 11:00:30 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		write_output_shell(int fd_out, int fd_error)
{
	int		r;
	char	buff[BUFF_SIZE + 1];

	if (fd_out > -1)
	{
		while ((r = read(fd_out, buff, BUFF_SIZE)) > 0)
		{
			buff[r] = '\0';
			write(1, buff, r);
		}
		if (r == -1)
			exit_error("4 Read has encountered a problem.");
	}
	if (fd_error > -1)
	{
		while ((r = read(fd_error, buff, BUFF_SIZE)) > 0)
		{
			buff[r] = '\0';
			write(2, buff, r);
		}
		if (r == -1)
			exit_error("3 Read has encountered a problem.");
	}
	close(fd_out);
	close(fd_error);
}
