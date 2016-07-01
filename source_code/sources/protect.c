/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 18:28:33 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 20:20:48 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*protect_all(char *line)
{
	static char	*syntax = SYNTAX;
	char		protect[2];
	char		*tmp;
	int			i;

	if (!has_syntax_in(line))
		return (line);
	protect[1] = '\0';
	i = 0;
	while (syntax[i])
	{
		if (ft_strchr(line, syntax[i]))
		{
			protect[0] = syntax[i];
			tmp = ft_strf("\033@%d", (int)protect[0]);
			line = ft_replace(line, protect, tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (line);
}

char	*protect(char *line)
{
	if (line == NULL)
		return (NULL);
	line = protect_backslash(line);
	line = protect_citation(line);
	return (line);
}

char	*protect_editor(char *line)
{
	if (line == NULL)
		return (NULL);
	if (ft_strchr(line, '!'))
	{
		line = protect_backslash_with_backslash(line);
		line = protect_citation(line);
	}
	return (line);
}

char	*unprotect(char *line)
{
	char		*syntax;
	char		protect[2];
	char		*tmp;
	char		*tmp2;

	if (!line)
		return (line);
	if (!ft_strchr(line, '\033'))
		return (line);
	syntax = SYNTAX;
	protect[0] = *syntax;
	protect[1] = '\0';
	while (protect[0])
	{
		tmp2 = ft_itoa((int)protect[0]);
		tmp = ft_strjoin("\033@", tmp2);
		line = ft_replace(line, tmp, protect);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		syntax++;
		protect[0] = *syntax;
	}
	return (line);
}
