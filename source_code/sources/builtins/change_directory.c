/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:58:07 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/27 19:57:26 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	change_directory(t_command *command, t_shell *shell, int out, int err)
{
	t_cmd_param		*params;
	char			*path;
	int				fds[2];

	fds[0] = out;
	fds[1] = err;
	change_status(shell, 1);
	path = NULL;
	params = parse_arguments(command, "PL", "");
	if (check_params(params, shell, fds, &path))
	{
		if (path)
		{
			change_current_directory(shell, params, path, fds);
			free(path);
		}
	}
	goto_begin_args(&params);
	free_options_list(&params);
}
