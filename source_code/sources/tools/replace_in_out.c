/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:30:03 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 17:10:34 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*replace_begin(char *str, int *i, char *to_del, char *to_put)
{
	char	*result;
	int		len;

	len = *i + ft_strlen(to_del);
	result = ft_strf("%.*s%s%s", *i, str, to_put, &str[len]);
	ft_strdel(&str);
	*i -= 1;
	return (result);
}

char			*replace_in(char *str, char *del, char *put, char *syntax)
{
	int		i;
	int		inside;
	char	begin;
	int		r;

	if (ft_strstr(str, del) == NULL)
		return (str);
	i = 0;
	inside = 0;
	begin = 0;
	while (str[i])
	{
		r = update_inside(&begin, str, &i, syntax);
		if (r)
			inside += r;
		else if (inside && ft_strncmp(&str[i], del, ft_strlen(del)) == 0)
		{
			str = replace_begin(str, &i, del, put);
		}
		i++;
	}
	return (str);
}

char			*replace_out(char *str, char *del, char *put, char *syntax)
{
	int		i;
	int		inside;
	char	begin;
	int		r;

	if (ft_strstr(str, del) == NULL)
		return (str);
	i = 0;
	inside = 0;
	begin = 0;
	while (str[i])
	{
		r = update_inside(&begin, str, &i, syntax);
		if (r)
			inside += r;
		else if (!inside && ft_strncmp(&str[i], del, ft_strlen(del)) == 0)
		{
			str = replace_begin(str, &i, del, put);
		}
		i++;
	}
	return (str);
}
