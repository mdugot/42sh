/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 15:05:41 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/30 12:13:49 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "toolkit.h"
#include "sh21.h"
#include "history.h"
#include <unistd.h>
#include <stdlib.h>

int		get_basic_input(t_shprop *shell)
{
	int read_ret;

	if ((read_ret = get_next_line(STDIN_FILENO, &(shell)->input)) <= 0)
		return (0);
	shell->hist->line = ft_strdup(shell->input);
	return (1);
}

int		special_input(int read_ret, t_shprop *shell)
{
	if (read_ret == 0)
		return (1);
	else if (read_ret == -1)
		return (0);
	else if (read_ret != 1)
	{
		read_ret = handle_key(shell, read_ret);
		if (read_ret == 0)
			return (1);
		else if (read_ret == -1)
			return (0);
	}
	return (-1);
}

int		get_input(t_shprop *shell, int (*handle)(t_shprop *, int))
{
	int		read_ret;

	if (shell->term->term_name)
	{
		reinit_termios(shell->term);
		while (interrupt(-1) == 0)
		{
			read_ret = get_one_input();
			if (interrupt(-1) == 1)
				return (1);
			if (read_ret != -1)
			{
				if (shell->size_changed)
					reprint_all_line(shell);
				read_ret = handle(shell, read_ret);
				if ((read_ret = special_input(read_ret, shell)) != -1)
					return (read_ret);
			}
		}
	}
	else
		return (get_basic_input(shell));
	if (interrupt(-1) == 1)
		return (1);
	return (0);
}

void	complete_line(t_shprop *shell)
{
	char	*save_input;
	char	*new_input;

	ft_strdel(&shell->prompt);
	shell->prompt = ft_strdup("> ");
	ft_putstr_fd(shell->prompt, shell->term->fd);
	shell->prompt_len = 2;
	save_input = ft_strdup(shell->input);
	ft_strdel(&shell->input);
	new_input = NULL;
	shell->curs_pos = 0;
	get_input(shell, &handle_edit_keys);
	if (shell->input)
	{
		new_input = ft_strjoin(save_input, shell->input);
		ft_strdel(&shell->input);
	}
	else if (interrupt(-1) == 0)
		new_input = ft_strdup(save_input);
	ft_strdel(&save_input);
	shell->input = new_input;
}

char	*get_next_command(t_shell *shell)
{
	if (shell->edit->prompt)
		ft_strdel(&(shell->edit)->prompt);
	shell->edit->prompt = print_prompt(shell, &shell->edit->prompt_len);
	ft_printf_fd(shell->edit->term->fd, "%s", shell->edit->prompt);
	if (get_input(shell->edit, &handle_key) == 0)
		clean_exit(shell->edit->term, 1, shell);
	if (shell->edit->term->term_name)
	{
		while (!is_closed(shell->edit->input, "\"'`([{") && interrupt(-1) == 0)
			complete_line(shell->edit);
	}
	if (!search_in_hist(shell->edit))
	{
		goto_end_list(shell->edit);
		ft_strdel(&(shell->edit->hist)->line);
		return (NULL);
	}
	hist_update(shell->edit, 0);
	if (shell->edit->input && interrupt(-1) != 1)
		append_hist(shell->edit);
	return (shell->edit->input);
}
