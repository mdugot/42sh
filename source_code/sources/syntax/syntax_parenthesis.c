/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 17:06:48 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/30 13:52:07 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*correct_parenthesis(char *line)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	if (!line)
		return (line);
	i = 0;
	while (line[i])
	{
		tmp = &line[i];
		if (!pass_citation(line, &i))
		{
			if (!is_escaped(line, &line[i]) && ft_strchr("()", *tmp))
			{
				tmp2 = ft_strf("%.*s %c %s", i, line, line[i], &tmp[1]);
				ft_strdel(&line);
				line = tmp2;
				i += 3;
			}
			else
				i++;
		}
	}
	return (line);
}
