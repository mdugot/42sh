/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 14:14:33 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/28 10:16:27 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

void			free_options_list(t_cmd_param **parsed)
{
	if (*parsed)
	{
		if ((*parsed)->args)
		{
			free_options_list(&(*parsed)->args);
			(*parsed)->args = NULL;
		}
	}
	if (*parsed)
	{
		if ((*parsed)->next)
		{
			free_options_list(&(*parsed)->next);
			(*parsed)->next = NULL;
		}
		free((*parsed)->param);
		free((*parsed));
	}
}

t_cmd_param		*bad_param(t_cmd_param **params, char *param,
		char *no_args, char *single_args)
{
	char	bad_argument[2];
	int		i;
	char	*valid_params;

	valid_params = ft_strjoin(no_args, single_args);
	i = 1;
	ft_bzero(bad_argument, sizeof(bad_argument));
	while (param[i])
	{
		bad_argument[0] = param[i];
		i++;
		if (!ft_strchr(valid_params, bad_argument[0]))
			break ;
	}
	if (i == 1)
		bad_argument[0] = '-';
	free_options_list(params);
	*params = cmd_param_new(ft_strdup("fail"), 1);
	(*params)->args = cmd_param_new(ft_strdup(bad_argument), 1);
	free(valid_params);
	return (*params);
}

static void		push_param(t_command *cmd, int *i, t_cmd_param *parsed)
{
	(*i)++;
	if (cmd->argv[*i] && is_option(cmd->argv[*i]) == 0)
		cmd_arg_push(parsed, cmd_param_new(ft_strdup(cmd->argv[*i]), 0));
	else
		(*i)--;
}

static void		push_other_params(t_cmd_param **parsed, t_command *cmd, int i)
{
	while (cmd->argv[i])
	{
		while (!find_existing_param(parsed, "other"))
			cmd_param_push(parsed, cmd_param_new(ft_strdup("other"), 1));
		cmd_arg_push(*parsed, cmd_param_new(ft_strdup(cmd->argv[i]), 0));
		i++;
	}
}

t_cmd_param		*parse_arguments(t_command *cmd, char *no_args,
		char *single_args)
{
	t_cmd_param	*parsed;
	int			i;
	int			option_type;

	parsed = NULL;
	i = 0;
	if (cmd->argc <= 1)
		return (NULL);
	while (cmd->argv[++i])
	{
		option_type = find_and_add_options(&parsed, cmd->argv[i],
				no_args, single_args);
		if (option_type == 2)
			push_param(cmd, &i, parsed);
		else if (option_type == 3)
			i++;
		else if (option_type == 0)
			return (bad_param(&parsed, cmd->argv[i], no_args, single_args));
		if (option_type == -1 || option_type == 3)
			break ;
	}
	push_other_params(&parsed, cmd, i);
	goto_begin_args(&parsed);
	return (parsed);
}
