/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 13:23:44 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/15 14:21:44 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"
#include "toolkit.h"

void		free_shell_input(t_shprop *shell)
{
	free(shell->input);
	shell->input = NULL;
	shell->curs_pos = 0;
	shell->input_len = 0;
}
