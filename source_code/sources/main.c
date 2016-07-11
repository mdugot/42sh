/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:11:30 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 19:40:17 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "sh21.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include "toolkit.h"
#include <fcntl.h>
#include "libft.h"

static void	arg_error(int argc, char **argv)
{
	(void)argv;
	if (argc >= 2)
	{
		ft_putendl_fd("Unknown option.", 2);
		ft_putendl_fd("Usage: 42sh", 2);
		exit(1);
	}
}

static int	void_line(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_strchr(" \t\n", *str))
			return (0);
		str++;
	}
	return (1);
}

static void	loop_command(t_shprop *shprop, t_shell *shell, char *str)
{
	t_command	*command;

	if (!void_line(str) && syntax_error(str) == 0)
	{
		command = cut_semicolon(shell, str);
		rst_termios(shprop->term);
		init_signal(shprop->term, 0);
		command->first = 1;
		execute(shell, command, NEXT_DEFAULT);
		init_signal(shprop->term, 1);
		free_command(command);
	}
}

int		main(int argc, char **argv, char **environ)
{
	t_shprop	*shprop;
	t_shell		*shell;
	char		*str;

	arg_error(argc, argv);
	shprop = init_shell(environ);
	init_signal(shprop->term, 1);
	shell = new_shell(environ, shprop);
	shprop->sh_ptr = (void *)shell;
	return_term(shprop->term);
	while (1)
	{
		reinit_termios(shprop->term);
		shell->to_kill = 0;
		str = ft_strdup(get_next_command(shell));
		str = correct_syntax_redirection(str);
		loop_command(shprop, shell, str);
		ft_strdel(&str);
		interrupt(0);
		free_shell_input(shell->edit);
	}
	free_shell(shell);
	return (0);
}
