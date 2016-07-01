/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:27:53 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 09:28:18 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include "history.h"

/*
** history options :
** -d [n] : delete the n entry in the history
** -c clear the history
** -s [...] add the followind params in the history
*/

static int		history2(t_cmd_param *params, int e, int *count_anrw,
					t_shell *sh)
{
	*count_anrw = check_anrw(params);
	if (*count_anrw > 1)
	{
		history_errors(5, "-anrw", e);
		return (1);
	}
	else if (find_existing_param(&params, "c"))
	{
		option_c(sh->edit);
		return (1);
	}
	return (0);
}

static int		history3(t_cmd_param *params, t_hist **hist, int e, int o)
{
	if (find_existing_param(&params, "d"))
	{
		delete_item_by_id(*hist, params, e);
		return (1);
	}
	else if (find_existing_param(&params, "p")
			|| find_existing_param(&params, "s"))
	{
		handle_ps(*hist, params, o);
		return (1);
	}
	return (0);
}

static int		history0(t_hist **hist, int o, t_command *cmd)
{
	if (cmd->argc == 1)
	{
		print_history(*hist, 0, o);
		return (1);
	}
	return (0);
}

static void		history4(t_cmd_param **params)
{
	goto_begin_args(params);
	free_options_list(params);
}

void			history(t_shell *sh, t_command *cmd, int o, int e)
{
	t_hist		**hist;
	t_cmd_param	*params;
	int			count_anrw;

	hist = &(sh->edit)->hist;
	params = NULL;
	if (history0(hist, o, cmd) == 0)
	{
		params = parse_arguments(cmd, "canrwps", "d");
		if (params)
		{
			if (ft_strcmp(params->param, "fail") == 0)
				history_errors(7, params->args->param, e);
			else
			{
				if ((history2(params, e, &count_anrw, sh) == 0 ||
					history3(params, hist, e, o) == 0) && count_anrw)
					handle_anrw(cmd, *hist, params, sh->edit->hist_dir);
				else if (find_existing_param(&params, "other"))
					print_n_last_lines(cmd, params, e, o);
				goto_end_hist(&(sh->edit->hist));
			}
			history4(&params);
		}
	}
}
