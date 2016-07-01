/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompose_condition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:45:15 by mdugot            #+#    #+#             */
/*   Updated: 2016/05/07 17:14:08 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_command	*last_command(t_command *c)
{
	if (c->next == NULL)
		return (c);
	else
		return (last_command(c->next));
}

t_command	*cut_or(char *line)
{
	t_command	*result;
	t_command	*tmp;
	char		**split;
	int			i;

	if (line == NULL)
		return (secure_alloc(sizeof(t_command)));
	split = ft_explode(line, "||");
	result = cut_pipe(split[0]);
	i = 1;
	tmp = last_command(result);
	while (split[0] && split[i])
	{
		tmp->next_type = NEXT_OR;
		tmp->next = cut_pipe(split[i]);
		tmp = last_command(tmp);
		i++;
	}
	ft_deltab((void*)split, ft_strsplit_size(split));
	return (result);
}

t_command	*cut_and(char *line)
{
	t_command	*result;
	t_command	*tmp;
	char		**split;
	int			i;

	if (line == NULL)
		return (secure_alloc(sizeof(t_command)));
	split = ft_explode(line, "&&");
	result = cut_or(split[0]);
	i = 1;
	tmp = last_command(result);
	while (split[0] && split[i])
	{
		tmp->next_type = NEXT_AND;
		tmp->next = cut_or(split[i]);
		tmp = last_command(tmp);
		i++;
	}
	ft_deltab((void*)split, ft_strsplit_size(split));
	return (result);
}
