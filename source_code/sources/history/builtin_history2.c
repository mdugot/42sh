/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:28:04 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 09:29:12 by rsibiet          ###   ########.fr       */
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

int		print_n_last_lines(t_command *cmd
		, t_cmd_param *param, int err_fd, int out_fd)
{
	int		i;
	int		id;
	char	*arg;
	t_hist	*hist;

	hist = cmd->shell->edit->hist;
	arg = param->args->param;
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (history_errors(6, arg, err_fd));
		i++;
	}
	id = (goto_begin_hist(&hist) - ft_atoi(arg)) + 1;
	i = 0;
	while (id && hist->prev)
	{
		i++;
		if (i >= id)
			print_history_line(hist, i, 5, out_fd);
		hist = hist->prev;
	}
	return (1);
}

int		handle_anrw(t_command *cmd, t_hist *hist
		, t_cmd_param *params, char *hist_path)
{
	char	*filename;

	if (find_existing_param(&params, "other"))
		filename = params->args->param;
	else
		filename = hist_path;
	if (find_existing_param(&params, "a"))
		return (option_a(hist, filename));
	else if (find_existing_param(&params, "r"))
		return (option_r(cmd, filename));
	else if (find_existing_param(&params, "n"))
		option_n(cmd, filename);
	else if (find_existing_param(&params, "w"))
		return (option_w(hist, filename));
	return (0);
}

int		handle_ps(t_hist *hist, t_cmd_param *params, int out_fd)
{
	int			len_params;
	t_cmd_param	*index;

	len_params = 0;
	hist = hist->next;
	if (find_existing_param(&params, "other"))
	{
		hist_delete_current_item(&hist);
		index = params->args;
		while (index)
		{
			len_params += ft_strlen(index->param) + 1;
			index = index->args;
		}
	}
	if (find_existing_param(&params, "p"))
		option_p(params, len_params, out_fd);
	if (find_existing_param(&params, "s"))
		option_s(params, hist, len_params);
	return (1);
}
