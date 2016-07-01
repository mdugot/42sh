/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 09:21:26 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/20 15:09:40 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include "toolkit.h"
#include "libft.h"

void	key_move_left(t_shprop *shell)
{
	t_term	*term;
	int		pos_in_wind;
	int		col_size;

	term = shell->term;
	col_size = term->ws.ws_col;
	pos_in_wind = shell->curs_pos + (int)shell->prompt_len;
	if (pos_in_wind > col_size - 1)
		pos_in_wind %= col_size;
	if (shell->input)
		if (shell->curs_pos > 0)
		{
			if (pos_in_wind == 0)
			{
				while (pos_in_wind < term->ws.ws_col)
				{
					T_SETMODE("nd");
					pos_in_wind++;
				}
				T_SETMODE("up");
			}
			else
				T_SETMODE("le");
			shell->curs_pos--;
		}
}

void	key_move_right(t_shprop *shell)
{
	t_term	*term;
	int		pos_in_wind;
	int		col_size;

	term = shell->term;
	col_size = term->ws.ws_col;
	pos_in_wind = shell->curs_pos + (int)shell->prompt_len;
	if (pos_in_wind > col_size)
		pos_in_wind %= col_size;
	if (pos_in_wind > term->ws.ws_col)
		col_size -= 2;
	else
		col_size -= 1;
	if (shell->input)
		if (shell->curs_pos < (int)shell->input_len)
		{
			if (pos_in_wind == col_size)
			{
				T_SETMODE("do");
				T_SETMODE("cr");
			}
			else
				T_SETMODE("nd");
			shell->curs_pos++;
		}
}

void	key_move_next_word(t_shprop *shell)
{
	if (shell->input)
	{
		if (shell->curs_pos < (int)shell->input_len)
			while (shell->curs_pos < (int)shell->input_len
					&& shell->input[shell->curs_pos] != ' ')
				key_move_right(shell);
		while (shell->curs_pos < (int)shell->input_len
				&& shell->input[shell->curs_pos] == ' ')
			key_move_right(shell);
	}
}

void	key_move_last_word(t_shprop *shell)
{
	if (shell->input)
	{
		if (shell->curs_pos > 0)
			while (shell->curs_pos > 0
					&& shell->input[shell->curs_pos - 1] != ' ')
				key_move_left(shell);
		while (shell->curs_pos > 0
				&& shell->input[shell->curs_pos - 1] == ' ')
			key_move_left(shell);
	}
}

int		goto_end_of_line(t_shprop *shell)
{
	t_term	*term;
	int		pos_in_wind;
	int		bak_pos;

	term = shell->term;
	bak_pos = shell->curs_pos;
	pos_in_wind = bak_pos + (int)shell->prompt_len;
	while ((pos_in_wind % term->ws.ws_col) != term->ws.ws_col - 1
			&& pos_in_wind < (int)shell->input_len + (int)shell->prompt_len)
	{
		key_move_right(shell);
		pos_in_wind++;
	}
	if (shell->curs_pos == bak_pos)
		return (0);
	if ((((shell->curs_pos + (int)shell->prompt_len) % term->ws.ws_col)
				== term->ws.ws_col - 1))
		return (1);
	return (0);
}
