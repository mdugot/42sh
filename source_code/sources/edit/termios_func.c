/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:03:26 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 23:06:30 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				init_termios(t_term *term, char **env)
{
	term->fd = STDIN_FILENO;
	if (!isatty(STDIN_FILENO))
		return (-1);
	term->term_name = find_env(env, "TERM");
	if (!term->term_name)
		term->term_name = "xterm-256color";
	if (tgetent(NULL, term->term_name) < 1)
	{
		term->term_name = NULL;
		return (-1);
	}
	if ((tcgetattr(term->fd, &(term)->term) == -1)
			|| (tcgetattr(term->fd, &(term)->term_bak) == -1))
	{
		ft_putendl_fd("Termios failed to init", 3);
		return (-1);
	}
	term->term.c_cc[VMIN] = 1;
	term->term.c_cc[VTIME] = 0;
	term->term.c_lflag &= ~(ICANON | ECHO);
	ioctl(term->fd, TIOCGWINSZ, &(term)->ws);
	if (tcsetattr(term->fd, 0, &(term)->term) == -1)
		return (-1);
	return (0);
}

int				reinit_termios(t_term *term)
{
	if (term->term_name)
	{
		ft_putstr_fd(T_GET_MODE("im"), term->fd);
		tcsetattr(term->fd, 0, &(term)->term);
	}
	return (0);
}

int				rst_termios(t_term *term)
{
	if (term->term_name)
	{
		ft_putstr_fd(T_GET_MODE("ei"), term->fd);
		tcsetattr(term->fd, 0, &(term)->term_bak);
	}
	return (0);
}
