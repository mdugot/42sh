/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 20:01:33 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/30 14:00:49 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "sh21.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <toolkit.h>
#include "history.h"

void			change_signal_mode(t_term *term, int mode)
{
	if (mode == 0)
		term->new_sigs.sa_flags = SA_RESTART;
	else
		term->new_sigs.sa_flags = 0;
}

t_shell			*shell_adress(t_shell *ad)
{
	static t_shell	*shell = NULL;

	if (ad == NULL)
		return (shell);
	shell = ad;
	return (shell);
}

void			rst_signals(t_term *term)
{
	int		i;

	i = 1;
	if (term->term_name)
	{
		while (i <= 31)
		{
			if (i != 20)
				sigaction(i, NULL, NULL);
			i++;
		}
	}
}

int				interrupt(int n)
{
	static int interrupt = 0;

	if (n > -1)
		interrupt = n;
	return (interrupt);
}

void			init_signal(t_term *term, int mode)
{
	int		i;

	if (term->term_name)
	{
		term->new_sigs.sa_handler = signal_handler;
		change_signal_mode(term, mode);
		i = 1;
		while (i <= 31)
		{
			if (i != 20)
				sigaction(i, &(term)->new_sigs, NULL);
			i++;
		}
	}
}
