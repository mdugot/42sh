/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_citation_backslash.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 18:08:31 by mressier          #+#    #+#             */
/*   Updated: 2016/06/30 13:16:02 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*protect_backslash(char *line)
{
	char protect[3];
	char *tmp;

	if (!ft_strchr(line, '\\'))
		return (line);
	protect[0] = '\\';
	protect[1] = ' ';
	protect[2] = '\0';
	line = replace_out(line, "\\\\", "\033@92", "\"'`([{");
	while (protect[1] <= '~')
	{
		if (ft_strstr(line, protect))
		{
			if (ft_strchr(SYNTAX, protect[1]))
			{
				tmp = ft_strf("\033@%d", (int)protect[1]);
				line = replace_out(line, protect, tmp, "\"'`([{");
				ft_strdel(&tmp);
			}
			else
				line = replace_out(line, protect, &protect[1], "\"'`([{");
		}
		protect[1] += 1;
	}
	return (line);
}

char		*protect_backslash_with_backslash(char *line)
{
	char protect[3];
	char *tmp;

	if (!ft_strchr(line, '\\'))
		return (line);
	protect[0] = '\\';
	protect[1] = ' ';
	protect[2] = '\0';
	line = replace_out(line, "\\\\", "\\\033@92", "\"'`([{");
	while (protect[1] <= '~')
	{
		if (ft_strstr(line, protect))
		{
			if (ft_strchr(SYNTAX, protect[1]))
			{
				tmp = ft_strf("\\\033@%d", (int)protect[1]);
				line = replace_out(line, protect, tmp, "\"'`([{");
				ft_strdel(&tmp);
			}
			else
				line = replace_out(line, protect, &protect[1], "\"'`([{");
		}
		protect[1] += 1;
	}
	return (line);
}

void		get_protect_citation(char **line, char *syntax, char protect[2])
{
	char		*tmp;
	int			i;

	i = 0;
	while (syntax[i])
	{
		if (ft_strchr(*line, syntax[i]))
		{
			protect[0] = syntax[i];
			tmp = ft_strf("\033@%d", (int)protect[0]);
			if (syntax[i] == '$')
				*line = replace_in(*line, protect, tmp, "'`(");
			else if (syntax[i] == '!')
				*line = replace_in(*line, protect, tmp, "'");
			else if (syntax[i] == '`')
				*line = replace_in(*line, protect, tmp, "'`(");
			else
				*line = replace_in(*line, protect, tmp, "\"'`(");
			ft_strdel(&tmp);
		}
		i++;
	}
}

char		*protect_citation(char *line)
{
	static char	*syntax = SYNTAX;
	char		protect[2];

	if (!is_in(line, syntax, "\"'`([{"))
		return (line);
	protect[1] = '\0';
	get_protect_citation(&line, syntax, protect);
	return (line);
}
