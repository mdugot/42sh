/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 18:19:09 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 18:19:10 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "sh21.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <toolkit.h>
#include "history.h"

static int		no_action_signal(int sig)
{
	if (sig == 3 || sig == 17 || sig == 18 || sig == 21 || sig == 22)
		return (1);
	return (0);
}

static void		handle_abort_signal(t_shell *shell, int sig)
{
	t_term *term;

	term = shell->edit->term;
	if (term->term_name)
	{
		rst_termios(term);
		rst_signals(term);
		kill(0, sig);
	}
}

static void		handle_sigwinch(t_shell *shell)
{
	t_shprop	*edit;
	t_term		*term;

	edit = shell->edit;
	term = edit->term;
	ioctl(term->fd, TIOCGWINSZ, &(term)->ws);
	shell->edit->size_changed = 1;
}

static void		handle_sigint(t_shell *shell, int sig)
{
	t_term	*term;
	t_hist	*hist;

	(void)sig;
	interrupt(1);
	term = shell->edit->term;
	key_move_end(shell->edit);
	goto_end_list(shell->edit);
	free_shell_input(shell->edit);
	hist = shell->edit->hist;
	if (hist && hist->line && !hist->prev)
		ft_strdel(&(shell->edit->hist)->line);
	T_PRINT("\n");
	T_SETMODE("cd");
}

void			signal_handler(int sig)
{
	t_shell		*sh;
	t_term		*term;

	sh = shell_adress(NULL);
	term = sh->edit->term;
	if (sig == SIGWINCH)
		handle_sigwinch(sh);
	else if (sig == SIGINT)
	{
		if (term->new_sigs.sa_flags == 0)
			handle_sigint(sh, sig);
		else
		{
			term->new_sigs.sa_flags = SA_RESTART;
			T_SETMODE("cr");
			T_SETMODE("cd");
		}
	}
	else if (!no_action_signal(sig))
		handle_abort_signal(sh, sig);
}
