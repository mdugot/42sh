/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:02:26 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 21:37:57 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		protect_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		split[i] = protect_all(split[i]);
		i++;
	}
}

void			del_tmp(char **t1, char **t2, char **t3)
{
	ft_strdel(t1);
	ft_strdel(t2);
	ft_strdel(t3);
}

char			**split_subshell(char *arg, t_shell *sh, char *tmp, char *tmp2)
{
	char *subshell;
	char **split;

	while ((tmp = ft_strchr(arg, '`')))
	{
		tmp = ft_strdup(tmp);
		if ((tmp2 = ft_strchr(&tmp[1], '`')) == NULL)
		{
			ft_strdel(&tmp);
			break ;
		}
		tmp2[1] = '\0';
		tmp2 = chop_limit(unprotect(ft_strdup(tmp)));
		subshell = str_subshell(tmp2, sh);
		if (subshell[ft_strlen(subshell) - 1] == '\n')
			subshell[ft_strlen(subshell) - 1] = '\0';
		arg = ft_replace(arg, tmp, subshell);
		del_tmp(&subshell, &tmp2, &tmp);
	}
	replace_whitespace(arg);
	split = ft_strsplit(arg, ' ');
	protect_split(split);
	ft_strdel(&arg);
	return (split);
}
