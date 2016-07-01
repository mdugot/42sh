/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:24:39 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 22:21:09 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include "libft.h"
#include "history.h"

int		check_line(char **line)
{
	int		i;

	i = 0;
	if ((*line))
	{
		while ((*line)[i] == ' ')
			i++;
		if ((*line)[i++] == '!')
		{
			if ((*line)[i] == '!')
				return (1);
			while ((*line)[i] == ' ' && (*line)[i] != 0)
				i++;
			if ((*line)[i] && (*line)[i] != '!' && (*line)[i - 1] == ' ')
				(*line) = ft_str_renew(line, ft_strsub((*line),
							i, ft_strlen(*line) - i));
			else if (((*line)[i] == 0 || (*line)[i - 1] == ' '))
				return (handle_errors_excp("!", 1));
		}
		if (*line && ft_strlen(*line) == 0)
			return (no_match_free(line));
	}
	return (1);
}

void	error_match(char *match, char *chr, int err_code)
{
	if (!match)
		handle_errors_excp(chr, err_code);
}

int		no_match_free(char **to_replace)
{
	if (to_replace)
		ft_strdel(to_replace);
	return (0);
}
