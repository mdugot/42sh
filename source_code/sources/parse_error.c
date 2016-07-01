/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 14:49:08 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/20 16:56:37 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_void_line(char *str)
{
	if (str == NULL)
		return (1);
	if (*str == 0)
		return (1);
	while (*str)
	{
		if (ft_strchr(" \t\n", *str) == NULL)
			return (0);
		str++;
	}
	return (1);
}

int		has_parse_error(t_command *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!cmd->first && cmd->type == C_VOID)
		return (1);
	if (is_void_line(cmd->line) && !cmd->first)
		return (1);
	if (!is_void_line(cmd->line) && cmd->type == C_VOID)
		return (1);
	return (0);
}

void	add_parse_error(t_command *cmd)
{
	command_error(cmd, "parse error", NULL);
	if (cmd->pipe)
	{
		free_command(cmd->pipe);
		cmd->pipe = NULL;
	}
	if (cmd->next)
	{
		free_command(cmd->next);
		cmd->next = NULL;
	}
}

int		parse_error(t_command *cmd)
{
	if (!has_parse_error(cmd))
		return (0);
	add_parse_error(cmd);
	return (1);
}
