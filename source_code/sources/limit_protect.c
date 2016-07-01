/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_protect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 18:10:42 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 18:10:45 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	what_limit(char *line)
{
	if (line[0] == '"' && line[ft_strlen(line) - 1] == '"')
		return (line[0]);
	else if (line[0] == '\'' && line[ft_strlen(line) - 1] == '\'')
		return (line[0]);
	else if (line[0] == '`' && line[ft_strlen(line) - 1] == '`')
		return (line[0]);
	else if (line[0] == '(' && line[ft_strlen(line) - 1] == ')')
		return (line[0]);
	else if (line[0] == '[' && line[ft_strlen(line) - 1] == ']')
		return (line[0]);
	else if (line[0] == '{' && line[ft_strlen(line) - 1] == '}')
		return (line[0]);
	else
		return ('\0');
}

char	*chop_limit(char *line)
{
	char *result;

	result = ft_strdup(&line[1]);
	result[ft_strlen(result) - 1] = '\0';
	ft_strdel(&line);
	return (result);
}
