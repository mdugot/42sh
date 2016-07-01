/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 09:23:38 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/24 13:47:03 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <unistd.h>
#include "toolkit.h"
#include "libft.h"

void	key_move_up_history(t_shprop *shell)
{
	char	*bak_hist;

	key_move_end(shell);
	bak_hist = NULL;
	if (shell->hist->next)
	{
		if (shell->hist->line)
			bak_hist = ft_strdup(shell->hist->line);
		while (shell->input && shell->input_len > 0)
			key_delete_char(shell);
		ft_strdel(&shell->hist->line);
		shell->hist->line = bak_hist;
		shell->hist = shell->hist->next;
		if (shell->hist->line)
			insert_line_on_shell(shell, shell->hist->line);
	}
}

void	key_move_down_history(t_shprop *shell)
{
	key_move_end(shell);
	if (shell->hist->prev)
	{
		while (shell->input && shell->input_len > 0)
			key_delete_char(shell);
		shell->hist = shell->hist->prev;
		if (shell->hist->line)
			insert_line_on_shell(shell, shell->hist->line);
	}
}

void	update_hist_delete(t_shprop *shell)
{
	if (shell->hist)
	{
		if (!shell->hist->prev)
		{
			if (shell->input)
			{
				ft_strdel(&shell->hist->line);
				shell->hist->line = ft_strdup(shell->input);
			}
			else if (shell->hist->line)
			{
				ft_strdel(&shell->hist->line);
				shell->hist->line = NULL;
			}
		}
	}
}
