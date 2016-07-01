/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_on_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:32:33 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 12:39:32 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_command	*cut_pipe(char *line)
{
	t_command	*result;
	t_command	*tmp;
	char		**split;
	int			i;

	if (line == NULL)
		return (secure_alloc(sizeof(t_command)));
	split = ft_explode(line, "|");
	result = secure_alloc(sizeof(t_command));
	result->line = ft_strdup(split[0]);
	i = 1;
	tmp = result;
	while (split[0] && split[i])
	{
		tmp->pipe = secure_alloc(sizeof(t_command));
		tmp->pipe->pipe_previous = tmp;
		tmp->pipe->line = ft_strdup(split[i]);
		tmp = tmp->pipe;
		i++;
	}
	ft_deltab((void*)split, ft_strsplit_size(split));
	return (result);
}

t_command	*cut_semicolon(t_shell *shell, char *line)
{
	t_command	*result;
	t_command	*tmp;
	char		**split;
	int			i;

	(void)shell;
	line = ft_strdup(line);
	if (line == NULL)
		return (secure_alloc(sizeof(t_command)));
	line = protect(line);
	replace_whitespace(line);
	split = ft_explode(line, ";");
	result = cut_and(split[0]);
	i = 1;
	tmp = last_command(result);
	while (split[0] && split[i])
	{
		tmp->next_type = NEXT_DEFAULT;
		tmp->next = cut_and(split[i]);
		tmp = last_command(tmp);
		i++;
	}
	ft_deltab((void*)split, ft_strsplit_size(split));
	ft_strdel(&line);
	return (result);
}
