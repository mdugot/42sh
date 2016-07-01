/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:29:42 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/30 12:08:03 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include "libft.h"

int		handle_edit_keys(t_shprop *shell, int key)
{
	int ret;

	ret = 1;
	if (key == RIGHT_ARROW)
		key_move_right(shell);
	else if (key == LEFT_ARROW)
		key_move_left(shell);
	else if (key == HOME_KEY)
		key_move_home(shell);
	else if (key == END_KEY)
		key_move_end(shell);
	else if (key == BACKSPACE_KEY)
		key_delete_char(shell);
	else if (key == RETURN_KEY)
	{
		key_act_return(shell);
		return (0);
	}
	else if (key == 2117294875)
		key_delete_right(shell);
	else if (key == 16)
		sc_clear_screen(shell);
	else
		add_char_input(shell, key);
	return (ret);
}

int		handle_key(t_shprop *shell, int key)
{
	if (key == UP_ARROW || key == 2117425947)
		key_move_up_history(shell);
	else if (key == DOWN_ARROW || key == 2117491483)
		key_move_down_history(shell);
	else if (key == 4)
	{
		if (shell->input)
			key_delete_right(shell);
		else
			return (-1);
	}
	else if (key == 14)
		key_move_next_word(shell);
	else if (key == 2)
		key_move_last_word(shell);
	else if (key == 11)
		key_move_line_up(shell);
	else if (key == 12)
		key_move_line_down(shell);
	else if (key == 9)
		return (key_tab_search(shell));
	else if (!handle_edit_keys(shell, key))
		return (0);
	return (1);
}
