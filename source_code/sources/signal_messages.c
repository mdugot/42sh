/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:52:46 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 23:04:45 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

static void		signals_messages_2(int status)
{
	if (status == 12)
		ft_printf_fd(2, "Bad system call: %d\n", status);
	else if (status == 13)
		ft_printf_fd(2, "Segmentation fault: %d\n", status);
	else if (status == 14)
		ft_printf_fd(2, "Alarm clock: %d\n", status);
	else if (status == 15)
		ft_printf_fd(2, "Terminated: %d\n", status);
	else if (status == 24)
		ft_printf_fd(2, "Cputime limit exceeded: %d\n", status);
	else if (status == 25)
		ft_printf_fd(2, "Filesize limit exceeded: %d\n", status);
	else if (status == 26)
		ft_printf_fd(2, "Virtual timer expired: %d\n", status);
	else if (status == 27)
		ft_printf_fd(2, "Profiling timer expired: %d\n", status);
	else if (status == 30)
		ft_printf_fd(2, "User defined signal 1: %d\n", status);
	else if (status == 31)
		ft_printf_fd(2, "User defined signal 2: %d\n", status);
}

void			signals_messages(int status)
{
	if (status == 1)
		ft_printf_fd(2, "Hangup: %d\n", status);
	else if (status == 3)
		ft_printf_fd(2, "Quit: %d\n", status);
	else if (status == 4)
		ft_printf_fd(2, "Illegal instruction: %d\n", status);
	else if (status == 5)
		ft_printf_fd(2, "Trap: %d\n", status);
	else if (status == 6)
		ft_printf_fd(2, "Abort: %d\n", status);
	else if (status == 8)
		ft_printf_fd(2, "Floating point exception: %d\n", status);
	else if (status == 9)
		ft_printf_fd(2, "Killed: %d\n", status);
	else if (status == 10)
		ft_printf_fd(2, "Bus error: %d\n", status);
	else if (status == 11)
		ft_printf_fd(2, "Segmentation fault: %d\n", status);
	else
		signals_messages_2(status);
}

void			handle_error_messages(t_shell *shell)
{
	if (shell->last_status)
	{
		if (shell->last_status_type == ST_SIGNAL)
			signals_messages(shell->last_status);
	}
}
