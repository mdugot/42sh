/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 13:01:13 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/27 19:06:23 by udelorme         ###   ########.fr       */
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

static int	history_errors_2(int err_code, char *str_err, int err_fd)
{
	if (err_code == 6)
	{
		ft_putstr_fd(str_err, err_fd);
		ft_putendl_fd(": numeric argument required ", err_fd);
	}
	else if (err_code == 7)
	{
		ft_putchar_fd('-', err_fd);
		ft_putstr_fd(str_err, err_fd);
		ft_putendl_fd(": invalid option", err_fd);
		return (history_errors(4, "usage", err_fd));
	}
	else if (err_code == 5)
	{
		ft_putstr_fd("cannot use more than one of ", err_fd);
		ft_putendl_fd(str_err, err_fd);
	}
	return (err_code);
}

int			history_errors(int err_code, char *str_err, int err_fd)
{
	ft_putstr_fd("history: ", err_fd);
	if (err_code == 2)
	{
		ft_putstr_fd(str_err, err_fd);
		ft_putendl_fd(": position out of range", err_fd);
	}
	else if (err_code == 3)
	{
		ft_putstr_fd("-", err_fd);
		ft_putstr_fd(str_err, err_fd);
		ft_putendl_fd(": option requires an argument", err_fd);
		return (history_errors(4, "usage", err_fd));
	}
	else if (err_code == 4)
	{
		ft_putstr_fd(str_err, err_fd);
		ft_putendl_fd(": history [-c] [-d offset] [n] or history"
			" -awrn [filename] or history -ps arg [arg...]", err_fd);
	}
	else
		return (history_errors_2(err_code, str_err, err_fd));
	return (err_code);
}

void		print_history(t_hist *hist, int last_n, int out_fd)
{
	int	i;

	i = 0;
	if (last_n)
		while (last_n)
		{
			hist = hist->next;
			last_n--;
		}
	else
		while (hist->next)
		{
			hist = hist->next;
		}
	while (hist->prev)
	{
		i++;
		print_history_line(hist, i, 5, out_fd);
		hist = hist->prev;
	}
}

int			delete_item_by_id(t_hist *hist, t_cmd_param *param
		, int err_fd)
{
	int		id;

	if (count_arguments(param) < 1)
		return (history_errors(3, param->param, err_fd));
	else
		id = ft_atoi(param->args->param);
	if (id == 0)
		return (history_errors(2, param->args->param, err_fd));
	goto_begin_hist(&hist);
	while (id > 1 && hist->prev->prev)
	{
		hist = hist->prev;
		id--;
	}
	if (id > 1)
		return (history_errors(2, param->args->param, err_fd));
	hist_delete_current_item(&hist);
	return (0);
}

int			check_anrw(t_cmd_param *params)
{
	int	count_options;

	count_options = 0;
	if (find_existing_param(&params, "a"))
		count_options++;
	if (find_existing_param(&params, "r"))
		count_options++;
	if (find_existing_param(&params, "n"))
		count_options++;
	if (find_existing_param(&params, "w"))
		count_options++;
	if (count_options > 1)
		return (5);
	else if (count_options == 1)
		return (1);
	return (0);
}
