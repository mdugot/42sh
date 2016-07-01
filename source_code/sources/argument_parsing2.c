/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:18:54 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/29 23:01:45 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

int				count_arguments(t_cmd_param *param)
{
	int	i;

	i = 0;
	while (param && param->args)
	{
		param = param->next;
		i++;
	}
	return (i);
}

int				count_params(t_cmd_param *param)
{
	int	i;

	i = 0;
	while (param && param->args)
	{
		param = param->args;
		i++;
	}
	return (i);
}

char			*no_hyphen(char *option)
{
	if (*option == '-')
		option++;
	return (option);
}

int				find_and_add_options(t_cmd_param **params, char *options,
		char *no_arg, char *single_arg)
{
	int		type;
	int		pass;
	char	buf[2];

	type = 0;
	buf[1] = 0;
	pass = 0;
	if (options[0] != '-')
		return (-1);
	while (++options && *options)
	{
		buf[0] = *options;
		type = find_arg_type(options, no_arg, single_arg);
		if ((type == 2 && !pass) || type == 1)
		{
			pass++;
			while (!find_existing_param(params, buf))
				cmd_param_push(params, cmd_param_new(ft_strdup(buf), 1));
		}
		else
			return (type);
	}
	if (pass > 1)
		return (1);
	return (type);
}
