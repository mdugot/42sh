/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_str_acts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:30:38 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/30 12:13:51 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include "toolkit.h"
#include "libft.h"

void	add_char_input(t_shprop *shell, int key)
{
	t_term	*term;

	term = shell->term;
	if (ft_isprint(key))
	{
		ft_putchar_fd(key, term->fd);
		shell->input_len++;
		cur_pos_char_insert(shell, key);
		if (shell->hist && !shell->hist->prev)
			ft_str_renew(&(shell->hist)->line, ft_strdup(shell->input));
		shell->curs_pos++;
		if (shell->curs_pos >= (int)shell->input_len)
			if ((shell->curs_pos + shell->prompt_len) % term->ws.ws_col
					== 0)
			{
				T_PRINT(" ");
				key_move_left(shell);
				key_move_right(shell);
			}
		if (shell->input_len + shell->prompt_len > term->ws.ws_col
				&& shell->curs_pos < (int)shell->input_len)
			fill_lines(shell);
	}
}

void	insert_line_on_shell(t_shprop *shell, const char *line)
{
	char	to_print;
	int		i;

	i = 0;
	while (line[i])
	{
		to_print = line[i];
		if (ft_isprint(to_print))
			add_char_input(shell, to_print);
		i++;
	}
}

void	print_line_on_shell(t_shprop *shell, char *line)
{
	t_term	*term;
	char	to_print;
	int		i;

	term = shell->term;
	i = 0;
	while (line[i])
	{
		to_print = line[i];
		if (ft_isprint(to_print))
		{
			ft_putchar_fd(to_print, shell->term->fd);
			shell->curs_pos = (int)shell->input_len;
		}
		i++;
	}
	if ((shell->curs_pos + shell->prompt_len)
			% shell->term->ws.ws_col == 0)
	{
		T_PRINT(" ");
		key_move_left(shell);
		key_move_right(shell);
	}
}

void	key_delete_char(t_shprop *shell)
{
	t_term *term;

	term = shell->term;
	if (shell->curs_pos > 0)
	{
		if (ft_isprint(shell->input[shell->curs_pos - 1]))
		{
			key_move_left(shell);
			T_SETMODE("dc");
		}
		else
			shell->curs_pos--;
		cur_pos_char_delete(shell);
		shell->input_len--;
		if (shell->curs_pos <= (int)shell->input_len)
			fill_lines_delete(shell);
		update_hist_delete(shell);
	}
}

void	key_delete_right(t_shprop *shell)
{
	t_term *term;

	term = shell->term;
	if (shell->curs_pos >= 0 && shell->curs_pos < (int)shell->input_len)
	{
		T_SETMODE("dc");
		cur_pos_char_delete(shell);
		shell->input_len--;
		fill_lines_delete(shell);
		update_hist_delete(shell);
	}
}
