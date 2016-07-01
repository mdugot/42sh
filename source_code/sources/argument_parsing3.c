/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:18:46 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 10:18:47 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
** function find_arg_type()
** Return -1 if the option is not an option
**		ex : '-l' is an option / 'l' is NOT an option
** Return 0 if the option doesn't exist
** Return 1 if the option doesn't takes arguments
** Return 2 if the option takes one argument
** Return 3 if the option is a '--'
*/

int				find_arg_type(char *arg, char *no_arg, char *single_arg)
{
	if (ft_strchr(no_arg, *arg))
		return (1);
	else if (ft_strchr(single_arg, *arg))
		return (2);
	else if (*arg == '-' && *(arg + 1) == 0)
		return (3);
	else
		return (0);
}

int				is_option(char *arg)
{
	if (arg[0] == '-')
		return (1);
	else
		return (0);
}

t_cmd_param		*cmd_param_new(char *param, int is_option)
{
	t_cmd_param *new;

	new = (t_cmd_param *)malloc(sizeof(t_cmd_param));
	if (new)
	{
		new->param = param;
		new->is_option = is_option;
		new->next = NULL;
		new->prev = NULL;
		new->args = NULL;
	}
	return (new);
}

void			cmd_arg_push(t_cmd_param *current, t_cmd_param *new)
{
	while (current->args)
		current = current->args;
	current->args = new;
}

void			cmd_param_push(t_cmd_param **all, t_cmd_param *new)
{
	t_cmd_param *index;

	index = *all;
	if (!*all)
		*all = new;
	else
	{
		while (index->next)
			index = index->next;
		new->prev = index;
		index->next = new;
	}
}
