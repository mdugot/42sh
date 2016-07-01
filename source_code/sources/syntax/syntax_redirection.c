/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 15:38:31 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 21:00:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				pass_citation(char *line, int *i)
{
	char begin;

	begin = line[*i];
	if (begin != '"' && begin != '\'')
		return (0);
	*i += 1;
	while (line[*i] && (line[*i] != begin || is_escaped(line, &line[*i])))
		*i += 1;
	if (line[*i])
		*i += 1;
	pass_citation(line, i);
	return (1);
}

static char		*replace_line(char **line, int i, char *tmp, int n)
{
	char		*line_tmp;

	line_tmp = ft_strf("%.*s %.*s %s", i, *line, n, &(*line)[i], tmp);
	ft_strdel(line);
	return (line_tmp);
}

char			*correct_syntax_redirection(char *line)
{
	char	*tmp;
	int		i;
	int		n;

	if (!line)
		return (line);
	i = 0;
	line = correct_parenthesis(line);
	while (line[i])
	{
		tmp = &line[i];
		if (!pass_citation(line, &i))
		{
			if (!is_escaped(line, &line[i]) && (n = is_redirection(&tmp)))
			{
				line = replace_line(&line, i, tmp, n);
				i += n + 2;
			}
			else
				i++;
		}
	}
	return (line);
}
