/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint_all_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 18:25:22 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 18:25:24 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			reprint_all_line(t_shprop *shell)
{
	t_term	*term;
	int		bak_pos;

	term = shell->term;
	bak_pos = shell->curs_pos;
	if (shell->input)
	{
		T_SETMODE("cr");
		T_SETMODE("cd");
		ft_printf_fd(shell->term->fd, "%s", shell->prompt);
		if (shell->input)
			print_line_on_shell(shell, shell->input);
		while (shell->curs_pos > bak_pos)
			key_move_left(shell);
	}
	shell->size_changed = 0;
}
