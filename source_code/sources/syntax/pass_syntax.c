/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:22:05 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 12:22:06 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*move_tmp_or_get_error(char **str)
{
	char		*tmp;

	tmp = *str;
	if (is_syntax(&tmp))
		return (NULL);
	tmp = *str;
	if (is_redirection(&tmp))
		return (NULL);
	tmp = *str;
	if (ft_strchr("()", *tmp))
		return (NULL);
	return (tmp);
}

static void		move_str_by_pass_citation(char **str, char *tmp)
{
	int		i;

	while ((*str)[0] && !ft_strchr("\t \n`", (*str)[0]) && !is_syntax(&tmp))
	{
		i = 0;
		if (pass_citation(*str, &i))
			*str += i;
		else
			*str += 1;
		tmp = *str;
	}
}

int				pass_redirection(char **str)
{
	char	*tmp;

	if (is_redirection(str))
	{
		while ((*str)[0] && ft_strchr("\t \n", (*str)[0]))
			*str += 1;
		tmp = move_tmp_or_get_error(str);
		if (tmp == NULL)
			return (-1);
		move_str_by_pass_citation(str, tmp);
	}
	return (0);
}

void			pass_backquote(char **str, int *r)
{
	if (*str[0] == '\\')
		*r = 1;
	while (*str[0] == '\\')
	{
		*str += 1;
		if (*str[0])
			*str += 1;
	}
}
