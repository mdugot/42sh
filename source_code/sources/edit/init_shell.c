/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 09:12:24 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 23:06:28 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "toolkit.h"
#include <fcntl.h>
#include "history.h"

static t_term	*t_term_new(void)
{
	t_term *new;

	new = (t_term *)malloc(sizeof(t_term));
	if (new)
		new->term_name = NULL;
	return (new);
}

static char		*set_hist_file_dir(char **env)
{
	char		*home_var;
	char		*full_path;

	home_var = find_env(env, "HOME");
	if (!home_var)
		full_path = ft_strdup(".42sh_history");
	else
		full_path = join_paths(home_var, ".42sh_history");
	return (full_path);
}

int				init_history(t_shprop *new_shell)
{
	if (new_shell->hist_fd == STDOUT_FILENO)
	{
		ft_putendl_fd("42sh: stdin not open", 2);
		exit(1);
	}
	else if (new_shell->hist_fd == STDERR_FILENO)
	{
		ft_putendl_fd("42sh: stderr not open", 2);
		exit(1);
	}
	if (get_history(new_shell, new_shell->hist_fd) == -1)
		ft_putendl_fd("42sh: Failed to open history file.", 2);
	return (1);
}

t_shprop		*init_shell(char **env)
{
	t_shprop	*new;
	char		*hist_path;

	hist_path = set_hist_file_dir(env);
	new = (t_shprop *)malloc(sizeof(t_shprop));
	if (new)
	{
		new->env = ft_strdup_tab(env);
		new->prompt = NULL;
		new->input = NULL;
		new->term = t_term_new();
		init_termios(new->term, env);
		new->curs_pos = 0;
		new->input_len = 0;
		new->prompt_len = 0;
		new->size_changed = 0;
		new->hist_dir = hist_path;
		new->hist_trunc = 0;
		new->hist_fd = open(hist_path, O_CREAT | O_RDWR | O_APPEND, 0755);
		new->sh_ptr = NULL;
		init_history(new);
	}
	return (new);
}

void			clean_exit(t_term *term, int key_code, t_shell *sh)
{
	rst_termios(term);
	if (sh)
		free_shell(sh);
	exit(key_code);
}
