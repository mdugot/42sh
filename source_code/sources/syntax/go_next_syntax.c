/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:23:52 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 20:57:24 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	pass_redirection_and_get_error(char **str, int *r, int end)
{
	if (*str[0] == '\0' || *str[0] == end)
		return (*r == 1 ? 0 : -1);
	if (pass_redirection(str) == -1)
		return (-1);
	if (*str[0] == '\0' || *str[0] == end)
		return (*r == 1 ? 0 : -1);
	if (quote_error(str, r, end) == -1)
		return (-1);
	return (1);
}

static int	move_str(char **str, int *r, int end)
{
	int		syntax;

	syntax = is_syntax(str);
	if (!syntax && !ft_strchr("\n \t", *str[0]))
		*r = 1;
	if (!syntax && *str[0] && *str[0] != end)
		*str += 1;
	return (syntax);
}

int			go_next_syntax(char **str, char end)
{
	int		r;
	int		ret;
	int		syntax;

	r = -1;
	if (*str[0] == '\0' || *str[0] == end || quote_error(str, &r, end))
		return (-1);
	syntax = is_syntax(str);
	if (!syntax && !ft_strchr("\n \t", *str[0]))
		r = 1;
	while (!syntax)
	{
		if ((ret = pass_redirection_and_get_error(str, &r, end)) != 1)
			return (ret);
		syntax = move_str(str, &r, end);
	}
	return (r);
}
