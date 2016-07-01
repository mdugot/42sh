/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 15:56:42 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 14:58:32 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include "libft.h"

void	sc_clear_screen(t_shprop *shell)
{
	t_term	*term;
	int		bak_pos;

	bak_pos = shell->curs_pos;
	term = shell->term;
	T_SETMODE("cl");
	ft_printf_fd(shell->term->fd, "%s", shell->prompt);
	if (shell->input)
		print_line_on_shell(shell, shell->input);
	while (shell->curs_pos > bak_pos)
		key_move_left(shell);
}
