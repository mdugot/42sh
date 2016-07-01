/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_acts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:30:32 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/24 17:25:08 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include "toolkit.h"
#include "libft.h"

void	key_act_return(t_shprop *shell)
{
	t_term *term;

	term = shell->term;
	key_move_end(shell);
	shell->input_len = 0;
	T_PRINT("\n");
}

void	act_delete_line(t_shprop *shell)
{
	key_move_end(shell);
	while (shell->input && shell->input_len > 0)
		key_delete_char(shell);
}

int		key_tab_search(t_shprop *shell)
{
	char	*cur_word;
	int		search_ret;

	cur_word = NULL;
	search_ret = 0;
	if (shell->input)
	{
		cur_word = ft_cut_cur_word(shell->input, shell->curs_pos);
		if ((search_ret = search_in_dir(shell, cur_word)) && search_ret > 0)
		{
			free(cur_word);
			return (search_ret);
		}
		else if ((search_ret = complete_by_glob(shell, cur_word))
				&& search_ret > 0)
		{
			free(cur_word);
			return (search_ret);
		}
		if (cur_word)
			free(cur_word);
	}
	return (1);
}

void	fill_lines_delete(t_shprop *shell)
{
	char	to_reprint;
	int		bak_pos;
	t_term	*term;
	int		fp;

	term = shell->term;
	bak_pos = shell->curs_pos;
	T_SETMODE("vi");
	fp = 1;
	while (shell->input && (goto_end_of_line(shell) || fp))
	{
		fp = 0;
		T_SETMODE("ei");
		to_reprint = shell->input[shell->curs_pos];
		ft_putchar_fd(to_reprint, term->fd);
		T_SETMODE("im");
		key_move_right(shell);
		T_SETMODE("dc");
		if ((((shell->curs_pos + (int)shell->prompt_len) % term->ws.ws_col)
					== term->ws.ws_col - 1))
			T_SETMODE("ce");
	}
	while (shell->curs_pos > bak_pos)
		key_move_left(shell);
	T_SETMODE("ve");
}

void	fill_lines(t_shprop *shell)
{
	char	to_reprint;
	int		bak_pos;
	t_term	*term;

	term = shell->term;
	bak_pos = shell->curs_pos;
	T_SETMODE("vi");
	if (((shell->curs_pos + (int)shell->prompt_len)
				% shell->term->ws.ws_col) == 0)
	{
		to_reprint = shell->input[shell->curs_pos];
		ft_putchar_fd(to_reprint, shell->term->fd);
		shell->curs_pos++;
	}
	while (goto_next_line(shell))
	{
		to_reprint = shell->input[shell->curs_pos];
		ft_putchar_fd(to_reprint, shell->term->fd);
	}
	while (bak_pos != shell->curs_pos)
		key_move_left(shell);
	T_SETMODE("ve");
}
