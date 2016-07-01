/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_moves_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 09:25:54 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/21 14:32:48 by tomo-chan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include "toolkit.h"
#include "libft.h"

int		goto_next_line(t_shprop *shell)
{
	t_term	*term;
	int		pos_in_wind;
	int		bak_pos;

	term = shell->term;
	bak_pos = shell->curs_pos;
	pos_in_wind = bak_pos + (int)shell->prompt_len;
	if ((pos_in_wind % term->ws.ws_col) == 0
			&& pos_in_wind <= (int)shell->input_len + (int)shell->prompt_len)
	{
		key_move_right(shell);
		pos_in_wind++;
		bak_pos = shell->curs_pos;
	}
	while ((pos_in_wind % term->ws.ws_col) != 0
			&& pos_in_wind <= (int)shell->input_len + (int)shell->prompt_len)
	{
		key_move_right(shell);
		pos_in_wind++;
	}
	if (shell->curs_pos == bak_pos)
		return (0);
	if ((((shell->curs_pos + (int)shell->prompt_len) % term->ws.ws_col) == 0))
		return (1);
	return (0);
}

void	key_move_home(t_shprop *shell)
{
	if (shell->input)
		if (shell->curs_pos > 0)
			while (shell->curs_pos > 0)
				key_move_left(shell);
}

void	key_move_end(t_shprop *shell)
{
	if (shell->input)
		if (shell->curs_pos < (int)shell->input_len)
			while (shell->curs_pos < (int)shell->input_len)
				key_move_right(shell);
}

void	key_move_line_up(t_shprop *shell)
{
	t_term	*term;
	int		col_size;

	term = shell->term;
	col_size = term->ws.ws_col;
	if ((shell->curs_pos - term->ws.ws_col) >= 0)
	{
		while (col_size)
		{
			key_move_left(shell);
			col_size--;
		}
	}
}

void	key_move_line_down(t_shprop *shell)
{
	t_term	*term;
	int		col_size;

	term = shell->term;
	col_size = term->ws.ws_col;
	if ((shell->curs_pos + term->ws.ws_col) <= (int)shell->input_len)
	{
		while (col_size)
		{
			key_move_right(shell);
			col_size--;
		}
	}
}
